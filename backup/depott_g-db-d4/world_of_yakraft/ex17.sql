DELETE FROM character
WHERE now() - lastconn >= '1 year'::interval;
