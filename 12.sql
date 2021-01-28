SELECT title FROM movies WHERE id IN
(SELECT movie_id FROM stars WHERE person_id =
(SELECT id FROM people where name = 'Helena Bonham Carter'))
AND id IN
(SELECT movie_id FROM stars WHERE person_id =
(SELECT id FROM people where name = 'Johnny Depp'));