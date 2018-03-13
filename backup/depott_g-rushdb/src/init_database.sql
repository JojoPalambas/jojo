DROP TABLE IF EXISTS customer CASCADE;
DROP TABLE IF EXISTS artist CASCADE;
DROP TABLE IF EXISTS song CASCADE;
DROP TABLE IF EXISTS album CASCADE;
DROP TABLE IF EXISTS stock CASCADE;
DROP TABLE IF EXISTS rent CASCADE;
DROP TABLE IF EXISTS album_song CASCADE;
DROP TABLE IF EXISTS rent_history CASCADE;
DROP TABLE IF EXISTS delivery CASCADE;
DROP TABLE IF EXISTS rented_artist CASCADE;
DROP TABLE IF EXISTS artist_release CASCADE;

-- Contains the description of the customers
CREATE TABLE customer
(
    name            VARCHAR(64)         NOT NULL DEFAULT '',
    email           VARCHAR(64)         NOT NULL DEFAULT '',

    PRIMARY KEY (email)
);

-- Contains the description of the artists
CREATE TABLE artist
(
    name            VARCHAR(64)         NOT NULL DEFAULT '',
    birthdate       DATE                NOT NULL,

    PRIMARY KEY (name)
);

-- Contains the description of the artists
CREATE TABLE song
(
    id              SERIAL              NOT NULL,
    name            VARCHAR(64)         NOT NULL DEFAULT '',
    artist_name     VARCHAR(64)         NOT NULL DEFAULT '',
    duration        INT                 NOT NULL DEFAULT 0,

    UNIQUE (name, artist_name),
    CHECK (duration >= 0),

    PRIMARY KEY (id),
    FOREIGN KEY (artist_name) REFERENCES artist (name)
);

-- Contains the description of the albums
CREATE TABLE album
(
    name            VARCHAR(64)         NOT NULL DEFAULT '',

    PRIMARY KEY (name)
);

-- Contains the description of the stock
CREATE TABLE stock
(
    album_name      VARCHAR(64)         NOT NULL DEFAULT '',
    quantity        INT                 NOT NULL DEFAULT 1,

    CHECK (quantity > 0),

    PRIMARY KEY (album_name),
    FOREIGN KEY (album_name) REFERENCES album (name)
);

-- Makes the link between the songs and the albums
CREATE TABLE album_song
(
    album_name      VARCHAR(64)         NOT NULL DEFAULT '',
    song_id         INT                 NOT NULL,
    track           INT                 NOT NULL DEFAULT 1,

    PRIMARY KEY (album_name, track),
    FOREIGN KEY (album_name) REFERENCES album (name),
    FOREIGN KEY (song_id) REFERENCES song (id)
);

-- Contains the description of all the current rents
CREATE TABLE rent
(
    id              SERIAL              NOT NULL,
    customer_email  VARCHAR(64)         NOT NULL DEFAULT '',
    album_name      VARCHAR(64)         NOT NULL DEFAULT '',
    rent_time       DATE                NOT NULL,

    UNIQUE(customer_email, album_name),

    PRIMARY KEY (id),
    FOREIGN KEY (customer_email) REFERENCES customer (email),
    FOREIGN KEY (album_name) REFERENCES album (name)
);

-- Contains the history of all the rents, including the current ones
CREATE TABLE rent_history
(
    id              SERIAL              NOT NULL,
    customer_email  VARCHAR(64)         NOT NULL DEFAULT '',
    album_name      VARCHAR(64)         NOT NULL DEFAULT '',
    rent_time       DATE                NOT NULL,
    return_time     DATE,

    PRIMARY KEY (id),
    FOREIGN KEY (customer_email) REFERENCES customer (email),
    FOREIGN KEY (album_name) REFERENCES album (name)
);

-- Stores the result of the track_deliveries trigger
CREATE TABLE delivery
(
    id              SERIAL              NOT NULL,
    album_name      VARCHAR(64)         NOT NULL DEFAULT '',
    amount          INT                 NOT NULL DEFAULT 1,
    delivery_date   TIMESTAMP           NOT NULL,

    PRIMARY KEY (id),
    FOREIGN KEY (album_name) REFERENCES album (name)
);

-- Stores the result of the track_rented_artists trigger
CREATE TABLE rented_artist
(
    id              SERIAL              NOT NULL,
    artist_name     VARCHAR(64)         NOT NULL DEFAULT '',
    song_amount     INT                 NOT NULL DEFAULT 0,
    rent_date       DATE                NOT NULL,

    PRIMARY KEY (id),
    FOREIGN KEY (artist_name) REFERENCES artist (name)
);

-- Stores the result of the track_artists_releases trigger
CREATE TABLE artist_release
(
    id              SERIAL              NOT NULL,
    release_date    TIMESTAMP           NOT NULL,
    artist_name     VARCHAR(64)         NOT NULL DEFAULT '',

    PRIMARY KEY (id),
    FOREIGN KEY (artist_name) REFERENCES artist (name)
);
