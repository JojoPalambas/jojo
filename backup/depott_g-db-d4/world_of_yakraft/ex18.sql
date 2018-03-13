SELECT name FROM character
WHERE lastconn BETWEEN '2017-01-10 00:00:00'::timestamp
                   AND '2017-01-10 23:59:59'::timestamp;
