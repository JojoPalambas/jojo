SELECT creature_template.name FROM creature_template
JOIN loots ON creature_template.id = loots.creature_gid
              AND loots.item_id IN
(
    SELECT inventory.item_id FROM inventory
    JOIN character ON character.id = inventory.character_id
                      AND character.name = 'Kuro'
);
