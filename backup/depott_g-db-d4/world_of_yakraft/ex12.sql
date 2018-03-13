SELECT creature_template.name
FROM creature_template
JOIN creature
    ON creature.gid = creature_template.id
    JOIN quest
        ON quest.creature_start = quest.creature_end
           AND quest.creature_start = creature.id;
