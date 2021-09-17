SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
-- Name contains both actors
WHERE name IN ("Johnny Depp", "Helena Bonham Carter")
-- Grouping by the titles of their movies
GROUP BY title
-- Taking movies who's count is 2; ie. they're both in it
HAVING COUNT(title) = 2;