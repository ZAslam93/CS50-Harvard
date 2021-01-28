SELECT movies.title
FROM movies
JOIN ratings
ON ratings.movie_id = movies.id
WHERE movies.id IN
(SELECT movie_id FROM stars WHERE person_id =
(SELECT id FROM people WHERE name = 'Chadwick Boseman'))
ORDER BY ratings.rating DESC
LIMIT 5;

