SELECT AVG(rating) FROM ratins WHERE movie_id IN (SELECT id FROM movies WHERE year = 2012);
