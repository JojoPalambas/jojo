UPDATE character
SET level = 15
WHERE name = 'Tilon';

UPDATE character
SET level = level + 1
WHERE name = 'Kuro';

UPDATE character
SET max_health = (level+1 - gender) * 10;
