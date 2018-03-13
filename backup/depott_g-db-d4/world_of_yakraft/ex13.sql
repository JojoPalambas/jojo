SELECT creature_template.name
FROM creature_template
LEFT JOIN creature ON creature.gid = creature_template.id
WHERE creature.gid IS NULL;
