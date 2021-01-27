SELECT name FROM songs WHERE arist_id =
(SELECT id FROM artists WHERE name = 'Post Malone');