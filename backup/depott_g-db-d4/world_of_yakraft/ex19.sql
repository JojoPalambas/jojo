CREATE TABLE item
(
    id              SERIAL      NOT NULL,
    name            VARCHAR(64) NOT NULL DEFAULT '',
    rarity          INT         NOT NULL DEFAULT 1,
    icon_id         INT         NOT NULL DEFAULT 1,

    PRIMARY KEY (id)
);

CREATE TABLE inventory
(
    id              SERIAL      NOT NULL,
    item_id         INT         NOT NULL DEFAULT 1,
    character_id    INT         NOT NULL DEFAULT 1,

    PRIMARY KEY (id),
    FOREIGN KEY (character_id) REFERENCES character(id)
);

CREATE TABLE loots
(
    id              SERIAL      NOT NULL,
    item_id         INT         NOT NULL DEFAULT 1,
    creature_gid    INT         NOT NULL DEFAULT 1,

    PRIMARY KEY (id),
    FOREIGN KEY (creature_gid) REFERENCES creature_template(id)
);
