SELECT creature_template.name
FROM creature_template
JOIN creature ON creature.gid = creature_template.id
                 AND creature.id = 6;
