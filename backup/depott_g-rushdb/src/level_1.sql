DROP FUNCTION IF EXISTS duration_to_string CASCADE;
DROP FUNCTION IF EXISTS add_artist CASCADE;
DROP FUNCTION IF EXISTS add_album CASCADE;
DROP FUNCTION IF EXISTS add_song_to_album CASCADE;
DROP FUNCTION IF EXISTS add_song CASCADE;
DROP VIEW IF EXISTS view_artists CASCADE;
DROP VIEW IF EXISTS view_albums CASCADE;
DROP VIEW IF EXISTS view_songs CASCADE;

-- Functions

CREATE OR REPLACE FUNCTION duration_to_string(duration INT)
RETURNS VARCHAR(16) AS
$$
BEGIN
    IF duration > 0 THEN
        IF duration % 60 < 10 THEN
            RETURN CONCAT(duration / 60, ':0', duration % 60);
        ELSE
            RETURN CONCAT (duration / 60, ':', duration % 60);
        END IF;
    ELSE
        RETURN '0:00';
    END IF;
END
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION add_artist(name VARCHAR(64), birthdate DATE)
RETURNS BOOLEAN AS
$$
BEGIN
    INSERT INTO artist (name, birthdate)
    VALUES (name, birthdate);
    RETURN TRUE;
EXCEPTION
    WHEN OTHERS THEN
        RETURN FALSE;
END
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION add_album(name VARCHAR(64))
RETURNS BOOLEAN AS
$$
BEGIN
    INSERT INTO album (name)
    VALUES (name);
    RETURN TRUE;
EXCEPTION
    WHEN OTHERS THEN
        RETURN FALSE;
END
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION add_song_to_album(title VARCHAR(64),
                                             album VARCHAR(64),
                                             artist VARCHAR(64), track INT)
RETURNS BOOLEAN AS
$$
BEGIN
    INSERT INTO album_song (album_name, song_id, track)
    VALUES (album,
            (
                SELECT song.id FROM song
                WHERE song.name = title AND song.artist_name = artist
                LIMIT 1
            )
           , track);
    RETURN TRUE;
EXCEPTION
    WHEN OTHERS THEN
        RETURN FALSE;
END
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION add_song(title VARCHAR(64), album VARCHAR(64),
                                    artist VARCHAR(64), track INT, duration INT)
RETURNS BOOLEAN AS
$$
BEGIN
    -- Adds the song
    INSERT INTO song (name, artist_name, duration)
    VALUES (title, artist, duration);

    -- Links the song to the album
    INSERT INTO album_song (album_name, song_id, track)
    VALUES (album,
            (
                SELECT song.id FROM song
                WHERE song.name = title AND song.artist_name = artist
                LIMIT 1
            )
           , track);

    RETURN TRUE;
EXCEPTION
    WHEN OTHERS THEN
        RETURN FALSE;
END
$$ LANGUAGE plpgsql;

-- Views

CREATE OR REPLACE VIEW view_artists AS
SELECT artist.name AS artist,
       artist.birthdate AS birthdate,
       COUNT(*) AS songs
FROM artist
JOIN song ON song.artist_name = artist.name
GROUP BY artist.name
ORDER BY artist.name;

CREATE OR REPLACE VIEW view_albums AS
SELECT album.name AS album,
       -- Useful to handle the left join : NULL -> duration = 0
       CASE WHEN SUM(song.duration) IS NULL THEN 0
            WHEN SUM(song.duration) IS NOT NULL THEN COUNT(*)
       END AS songs,
       -- Same here
       CASE WHEN SUM(song.duration) IS NULL THEN '0:00'
            WHEN SUM(song.duration) IS NOT NULL
                THEN duration_to_string(SUM(song.duration)::INT)
       END AS duration
FROM album
LEFT JOIN album_song ON album_song.album_name = album.name
LEFT JOIN song ON album_song.song_id = song.id
GROUP BY album.name
ORDER BY album.name;

CREATE OR REPLACE VIEW view_songs AS
SELECT song.name AS music,
       song.artist_name AS artist,
       duration_to_string(song.duration) AS duration
FROM song
ORDER BY song.name, song.artist_name;
