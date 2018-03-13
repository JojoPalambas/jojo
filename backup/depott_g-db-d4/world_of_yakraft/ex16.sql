CREATE TABLE faction
(
    id       SERIAL       NOT NULL,
    color    INT          NOT NULL DEFAULT 0,
    name     VARCHAR(64)  NOT NULL DEFAULT '',
    PRIMARY KEY (id)
);

INSERT INTO faction
VALUES (DEFAULT, 65280, 'Enlightened');

ALTER TABLE creature
ADD faction_id INT;

ALTER TABLE creature
ADD FOREIGN KEY(faction_id) REFERENCES faction(id);
