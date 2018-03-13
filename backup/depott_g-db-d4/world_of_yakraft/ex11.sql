SELECT quest.title, creature_template.name
FROM quest
JOIN creature
    ON quest.creature_start = creature.id
    JOIN creature_template
        ON creature.gid = creature_template.id;
