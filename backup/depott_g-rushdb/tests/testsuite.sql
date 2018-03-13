SELECT '==============================================';

SELECT * FROM artist;

SELECT '==============================================';

SELECT add_artist('1995', '2008-08-27');
SELECT add_artist('Nekfeu', '1990-04-03');
SELECT add_artist('1995', '2013-05-14');

SELECT '==============================================';

SELECT * FROM artist;
SELECT * FROM album;

SELECT '==============================================';

SELECT add_album('Cyborg');
SELECT add_album('Dans la légende');
SELECT add_album('La source');
SELECT add_album('Dans la légende');
SELECT add_album('DAns lA léGEnde');

SELECT '==============================================';

SELECT * FROM album;
SELECT * FROM song;
SELECT * FROM album_song;

SELECT '==============================================';

SELECT add_song('Nekketsu', 'Cyborg', 'Nekfeu', 2, 4*60+43);
SELECT add_song('Humanoïde', 'Cyborg', 'Nekfeu', 2, 3*60+24);
SELECT add_song('Nekketsu', 'La source', '1995', 14, 3*60+24);
SELECT add_song('J''suis QLF', 'Dans la légende', 'PNL', 7, 4*60+20);
SELECT add_song('Comme Un Grand', 'La Suite', '1995', 2, 4*60+23);
SELECT add_song('Milliardaire', 'La source', 'Nekfeu', 2, 4*60+23);

SELECT '==============================================';

SELECT * FROM song;
SELECT * FROM album_song;

SELECT '==============================================';

SELECT add_song_to_album('Milliardaire', 'La source', 'Nekfeu', 16);
SELECT add_song_to_album('Milliardaire', 'La source', 'Nekfeu', 15);
SELECT add_song_to_album('Milliardaire2', 'La source', 'Nekfeu', 15);
SELECT add_song_to_album('Anonymous', 'La source', 'Unknown artist', 4);
SELECT add_song_to_album('Anonymous', 'Unknown album', 'Nekfeu', 3);

SELECT '==============================================';

SELECT * FROM song;
SELECT * FROM album_song;

SELECT '==============================================';

SELECT * FROM view_artists;
SELECT * FROM view_albums;
SELECT * FROM view_songs;

SELECT '==============================================';

SELECT * FROM customer;

SELECT '==============================================';

SELECT add_customer('Yolandi VISSER', 'yolandi.visser@test.io');
SELECT add_customer('John LENNON', 'yolandi.visser@test.io');
SELECT add_customer('John LENNON', 'lennon_j@test.io');

SELECT '==============================================';

SELECT * FROM customer;
SELECT * FROM stock;

SELECT '==============================================';

SELECT add_stock('Cyborg', 5);
SELECT add_stock('Dans la légende', 1);
SELECT add_stock('Unknown', 3);
SELECT add_stock('Cyborg', -1);

SELECT '==============================================';

SELECT * FROM stock;
SELECT * FROM rent;
SELECT * FROM rent_history;

SELECT '==============================================';

SELECT rent_album('lennon_j@test.io', 'Cyborg', '2016-01-05');
SELECT rent_album('yolandi.visser@test.io', 'Cyborg', '2016-01-05');
SELECT rent_album('lennon_j@test.io', 'Dans la légende', '2016-01-05');
SELECT rent_album('lennon_j@test.io', 'Cyborg', '2016-01-01');
SELECT rent_album('lennon_j@test.io', 'Cyborg', '2016-01-05');
SELECT rent_album('lennon_j@test.io', 'Cyborg', '2016-01-08');

SELECT '==============================================';

SELECT * FROM stock;
SELECT * FROM rent;
SELECT * FROM rent_history;

SELECT '==============================================';

SELECT return_album('lennon_j@test.io', 'Dans la légende', '2016-01-10');
SELECT return_album('yolandi.visser@test.io', 'Dans la légende', '2016-01-10');
SELECT rent_album('lennon_j@test.io', 'Dans la légende', '2016-01-15');

SELECT '==============================================';

SELECT * FROM stock;
SELECT * FROM rent;
SELECT * FROM rent_history;

SELECT '==============================================';

SELECT * FROM view_customers;
SELECT * FROM view_rents;
SELECT * FROM view_stocks;

SELECT '==============================================';

SELECT * FROM rent;
SELECT * FROM rent_history;

SELECT '==============================================';

SELECT * FROM get_current_rents('2016-01-10');
SELECT * FROM get_current_rents('2016-01-18');
SELECT * FROM get_current_rents('2016-01-14');

SELECT '==============================================';

SELECT * FROM album_song;
SELECT * FROM song;

SELECT '==============================================';

SELECT * FROM album_contents('La source');

SELECT '==============================================';

SELECT * FROM rent_history;

SELECT '==============================================';

SELECT add_stock('La source', 5);;
SELECT rent_album('lennon_j@test.io', 'La source', '2016-01-25');
SELECT return_album('lennon_j@test.io', 'La source', '2016-01-30');
SELECT rent_album('lennon_j@test.io', 'La source', '2016-02-15');
SELECT return_album('lennon_j@test.io', 'La source', '2016-03-15');
SELECT rent_album('lennon_j@test.io', 'La source', '2016-04-15');
SELECT return_album('lennon_j@test.io', 'La source', '2016-04-25');
SELECT rent_album('lennon_j@test.io', 'La source', '2016-05-26');

SELECT '==============================================';

SELECT * FROM rent_history;

SELECT '==============================================';

SELECT * FROM generate_bills(2016);
SELECT * FROM generate_bills_new(2016);

SELECT '==============================================';

SELECT * FROM rent_history;

SELECT '==============================================';

SELECT * FROM view_customer_favorites;

SELECT '==============================================';

SELECT * FROM view_deliveries;
SELECT * FROM view_rented_artists;
SELECT * FROM view_released_songs;

SELECT '==============================================';
