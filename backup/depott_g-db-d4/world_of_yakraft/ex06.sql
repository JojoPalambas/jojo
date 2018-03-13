SELECT title FROM quest
WHERE level_min BETWEEN 8 AND 10 AND (creature_start = creature_end OR gold >= 100);
