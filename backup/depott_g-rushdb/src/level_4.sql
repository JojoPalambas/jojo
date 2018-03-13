DROP FUNCTION IF EXISTS deliveries_tracker CASCADE;
DROP FUNCTION IF EXISTS artists_tracker CASCADE;
DROP FUNCTION IF EXISTS releases_tracker CASCADE;
DROP TRIGGER IF EXISTS track_deliveries ON stock CASCADE;
DROP TRIGGER IF EXISTS track_rented_artists ON rent CASCADE;
DROP TRIGGER IF EXISTS track_artists_releases ON song CASCADE;
DROP VIEW IF EXISTS view_deliveries CASCADE;
DROP VIEW IF EXISTS view_rented_artists CASCADE;
DROP VIEW IF EXISTS view_top_five CASCADE;
DROP VIEW IF EXISTS view_released_songs CASCADE;

-- Functions & triggers

CREATE OR REPLACE FUNCTION deliveries_tracker()
RETURNS TRIGGER AS
$$
BEGIN
    INSERT INTO delivery (album_name, amount, delivery_date)
    VALUES (NEW.album_name, NEW.quantity, now());
    RETURN NULL;
END
$$ LANGUAGE plpgsql;

CREATE TRIGGER track_deliveries
AFTER INSERT ON stock
FOR EACH ROW EXECUTE PROCEDURE deliveries_tracker();

CREATE OR REPLACE FUNCTION artists_tracker()
RETURNS TRIGGER AS
$$
DECLARE
    artist_name_it      VARCHAR(64);
BEGIN
    -- Lists the artists contained in the album to loop on them
    FOR artist_name_it IN
        SELECT song.artist_name
        FROM song
        JOIN album_song ON album_song.song_id = song.id
             AND album_song.album_name = NEW.album_name
    LOOP
        INSERT INTO rented_artist (artist_name, song_amount, rent_date)
        VALUES (artist_name_it,
            (
                SELECT COUNT(*) FROM album_song
                JOIN song ON album_song.song_id = song.id
                WHERE song.artist_name = artist_name_it
            ), NEW.rent_time);
    END LOOP;
    RETURN NULL;
END
$$ LANGUAGE plpgsql;

CREATE TRIGGER track_rented_artists
AFTER INSERT ON rent
FOR EACH ROW EXECUTE PROCEDURE artists_tracker();

CREATE OR REPLACE FUNCTION releases_tracker()
RETURNS TRIGGER AS
$$
BEGIN
    INSERT INTO artist_release (release_date, artist_name)
    VALUES (now(), NEW.artist_name);
    RETURN NULL;
END
$$ LANGUAGE plpgsql;

CREATE TRIGGER track_artists_releases
AFTER INSERT ON song
FOR EACH ROW EXECUTE PROCEDURE releases_tracker();

-- Views

CREATE OR REPLACE VIEW view_deliveries AS
SELECT delivery.album_name AS album,
       delivery.amount AS amount,
       TO_CHAR(delivery.delivery_date, 'DD/MM/YYYY HH24:MI:SS') AS date
FROM delivery
ORDER BY delivery.delivery_date, delivery.amount, delivery.album_name;

CREATE OR REPLACE VIEW view_rented_artists AS
SELECT rented_artist.artist_name AS artist,
       rented_artist.song_amount AS amount,
       TO_CHAR(rented_artist.rent_date, 'DD/MM/YYYY') AS date
FROM rented_artist
ORDER BY rented_artist.rent_date, rented_artist.artist_name;

CREATE OR REPLACE VIEW view_released_songs AS
SELECT artist_release.artist_name AS artist,
       artist_release.release_date AS date
FROM artist_release
ORDER BY artist_release.artist_name, artist_release.release_date;
