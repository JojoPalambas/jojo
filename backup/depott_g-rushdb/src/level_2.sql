DROP FUNCTION IF EXISTS add_customer CASCADE;
DROP FUNCTION IF EXISTS add_stock CASCADE;
DROP FUNCTION IF EXISTS rent_album CASCADE;
DROP FUNCTION IF EXISTS return_album CASCADE;
DROP VIEW IF EXISTS view_customers CASCADE;
DROP VIEW IF EXISTS view_rents CASCADE;
DROP VIEW IF EXISTS microview_album_rents CASCADE;
DROP VIEW IF EXISTS microview_album_stocks CASCADE;
DROP VIEW IF EXISTS view_stocks CASCADE;

-- Functions

CREATE OR REPLACE FUNCTION add_customer(name VARCHAR(64), email VARCHAR(64))
RETURNS BOOLEAN AS
$$
BEGIN
    INSERT INTO customer (name, email)
    VALUES (name, email);
    RETURN TRUE;
EXCEPTION
    WHEN OTHERS THEN
        RETURN FALSE;
END
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION add_stock(album VARCHAR(64), n INT)
RETURNS BOOLEAN AS
$$
BEGIN
    -- If the album is already in the stock
    IF album IN (
                    SELECT stock.album_name FROM stock 
                    WHERE stock.album_name = album
                ) THEN
        UPDATE stock
        SET stock.quantity = stock.quantity + n
        WHERE stock.album_name = album;
    -- If it is not
    ELSE
        INSERT INTO stock (album_name, quantity)
        VALUES (album, n);
    END IF;
    RETURN TRUE;
EXCEPTION
WHEN OTHERS THEN
    RETURN FALSE;
END
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION rent_album(customer_mail VARCHAR(64),
                                      album VARCHAR(64),
                                      RENT_DATE DATE)
RETURNS BOOLEAN AS
$$
BEGIN
    -- Checks whether the album is in stock
    IF album NOT IN (
                        SELECT album_name FROM stock
                    ) THEN
        RETURN FALSE;
    END IF;

    INSERT INTO rent (customer_email, album_name, rent_time)
    VALUES (customer_mail, album, RENT_DATE);
    -- If the album has been rented, stores the rent in rent_history
    -- and removes an album from the stock
    IF FOUND THEN
        INSERT INTO rent_history (customer_email, album_name, rent_time)
        VALUES (customer_mail, album, RENT_DATE);

        DELETE FROM stock
        WHERE quantity = 1 AND album_name = album;
        
        UPDATE stock
        SET quantity = quantity - 1
        WHERE album_name = album;
    END IF;
    RETURN TRUE;
EXCEPTION
    WHEN OTHERS THEN
        RETURN FALSE;
END
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION return_album(customer_mail VARCHAR(64),
                                        album VARCHAR(64),
                                        return_date DATE)
RETURNS BOOLEAN AS
$$
BEGIN
    -- Checks whether this customer has borrowed this album
    IF ROW(customer_mail, album) NOT IN
        (
            SELECT customer_email, album_name FROM rent
        ) THEN
        RETURN FALSE;
    END IF;

    DELETE FROM rent
    WHERE rent.customer_email = customer_mail
          AND rent.album_name = album;
    -- Places the album back in the stock
    IF album NOT IN
        (
            SELECT album_name FROM stock
        ) THEN
        INSERT INTO stock (album_name, quantity)
        VALUES (album, 1);
    ELSE
        UPDATE stock
        SET quantity = quantity + 1
        WHERE album_name = album;
    END IF;

    -- Writes the returning date in rent_history
    UPDATE rent_history
    SET return_time = return_date
    WHERE customer_email = customer_mail
          AND album_name = album
          AND return_time IS NULL;
    RETURN TRUE;
EXCEPTION
    WHEN OTHERS THEN
        RETURN FALSE;
END
$$ LANGUAGE plpgsql;

-- View

CREATE OR REPLACE VIEW view_customers AS
SELECT customer.email AS email,
       customer.name AS name,
       COUNT(*) AS total_rents,
       COUNT(*) - COUNT(rent_history.return_time) AS current_rents
FROM customer
JOIN rent_history ON rent_history.customer_email = customer.email
GROUP BY customer.email
ORDER BY customer.email;

CREATE OR REPLACE VIEW view_rents AS
SELECT rent_history.customer_email AS email,
       rent_history.album_name AS album,
       rent_history.rent_time AS begin,
       (rent_history.rent_time + '14 days'::INTERVAL)::DATE AS deadline,
       rent_history.return_time AS end
FROM rent_history
ORDER BY rent_history.rent_time DESC, rent_history.customer_email,
         rent_history.album_name;

-- View that lists all the albums and how many of them are rented
CREATE OR REPLACE VIEW microview_album_rents AS
SELECT album.name AS album,
       CASE WHEN rent.album_name IS NULL THEN 0
            WHEN rent.album_name IS NOT NULL THEN COUNT(*)
       END AS rented
FROM album
LEFT JOIN rent ON album.name = rent.album_name
GROUP BY album.name, rent.album_name;

CREATE OR REPLACE VIEW microview_album_stocks AS
SELECT album.name AS album,
       CASE WHEN stock.album_name IS NULL THEN 0
            WHEN stock.album_name IS NOT NULL THEN stock.quantity
       END AS stocked
FROM album
LEFT JOIN stock ON album.name = stock.album_name
GROUP BY album.name, stock.album_name;

CREATE OR REPLACE VIEW view_stocks AS
SELECT album.name AS album,
       microview_album_rents.rented + microview_album_stocks.stocked AS stock
FROM album
JOIN microview_album_rents ON microview_album_rents.album = album.name
JOIN microview_album_stocks ON microview_album_stocks.album = album.name
WHERE microview_album_rents.rented + microview_album_stocks.stocked > 0
ORDER BY album.name;
