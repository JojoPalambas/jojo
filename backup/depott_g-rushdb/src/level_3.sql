DROP FUNCTION IF EXISTS get_current_rents;
DROP FUNCTION IF EXISTS album_contents;
DROP FUNCTION IF EXISTS generate_bills;
DROP FUNCTION IF EXISTS generate_bills_new;
DROP VIEW IF EXISTS view_customer_favorites;

-- Functions

CREATE OR REPLACE FUNCTION get_current_rents(stock_date DATE)
RETURNS TABLE(album VARCHAR(64), mail VARCHAR(64)) AS
$$
BEGIN
    RETURN QUERY
    SELECT album_name, customer_email
    FROM rent_history
    WHERE rent_time <= stock_date AND (return_time IS NULL
                                       OR return_time >= stock_date);
END
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION album_contents(album VARCHAR(64))
RETURNS TABLE(n INT, title VARCHAR(64),
              artist VARCHAR(64), duration VARCHAR(16)) AS
$$
BEGIN
    RETURN QUERY
    SELECT album_song.track, song.name, song.artist_name,
           duration_to_string(song.duration)
    FROM album_song
    JOIN song ON album_song.song_id = song.id
                 AND album_song.album_name = album
    ORDER BY album_song.track;
--EXCEPTION
--    WHEN OTHERS THEN
--        RETURN FALSE;
END
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION generate_bills(bill_year INT)
RETURNS TABLE(name VARCHAR(64), mail VARCHAR(64), price REAL) AS
$$
BEGIN
    RETURN QUERY
    SELECT customer.name AS name,
           customer.email AS mail,
                    -- If the return is not late
           SUM(CASE WHEN rent_history.return_time IS NOT NULL
                    AND rent_history.return_time
                        BETWEEN rent_history.rent_time
                        AND rent_history.rent_time + '14 days'::INTERVAL
                    THEN 0.42
                    -- Else
                    WHEN TRUE THEN 0.84
               END)::REAL AS price
    FROM customer
    JOIN rent_history ON customer.email = rent_history.customer_email
    WHERE rent_history.return_time IS NOT NULL
          AND EXTRACT(YEAR FROM rent_history.return_time)::INT = bill_year
    GROUP BY customer.name, customer.email;
--EXCEPTION
--    WHEN OTHERS THEN
--        RETURN FALSE;
END
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION generate_bills_new(bill_year INT)
RETURNS TABLE(name VARCHAR(64), mail VARCHAR(64), price REAL) AS
$$
BEGIN
    RETURN QUERY
    SELECT customer.name AS name,
           customer.email AS mail,
                    -- If the return is not late
           SUM(CASE WHEN rent_history.return_time IS NOT NULL
                    AND rent_history.return_time
                        BETWEEN rent_history.rent_time
                        AND rent_history.rent_time + '14 days'::INTERVAL
                    THEN 0.42
                    -- If it is late by less than 4 days
                    WHEN rent_history.return_time IS NOT NULL
                    AND rent_history.return_time
                        BETWEEN rent_history.rent_time
                        AND rent_history.rent_time + '18 days'::INTERVAL
                    THEN 0.84
                    -- If it is very late
                    WHEN rent_history.return_time IS NOT NULL
                    AND rent_history.return_time
                        > rent_history.rent_time + '18 days'::INTERVAL
                    THEN 0.42 + 0.10 *
                    (
                        rent_history.return_time - rent_history.rent_time - 18
                    )
               END)::REAL AS price
    FROM customer
    JOIN rent_history ON customer.email = rent_history.customer_email
    WHERE rent_history.return_time IS NOT NULL
          AND EXTRACT(YEAR FROM rent_history.return_time)::INT = bill_year
    GROUP BY customer.name, customer.email;
--EXCEPTION
--    WHEN OTHERS THEN
--        RETURN FALSE;
END
$$ LANGUAGE plpgsql;

-- Lists all the songs listened by all thye customers
CREATE OR REPLACE VIEW microview_customers_songs AS
SELECT customer.name AS customer,
       customer.email AS mail,
       album_song.album_name AS album,
       artist.name AS artist,
       artist.birthdate AS artist_birthdate,
       song.name AS song
FROM customer
JOIN rent_history ON customer.email = rent_history.customer_email
JOIN album_song ON album_song.album_name = rent_history.album_name
JOIN song ON song.id = album_song.song_id
JOIN artist ON artist.name = song.artist_name;

CREATE OR REPLACE VIEW view_customer_favorites AS
SELECT microview_customers_songs.customer AS customer,
       microview_customers_songs.mail AS mail,
       microview_customers_songs.artist AS artist,
       microview_customers_songs.artist_birthdate AS artist_birthdate,
       COUNT(*) AS songs_listened
FROM microview_customers_songs
GROUP BY microview_customers_songs.customer,
         microview_customers_songs.mail,
         microview_customers_songs.artist,
         microview_customers_songs.artist_birthdate
ORDER BY microview_customers_songs.mail;
