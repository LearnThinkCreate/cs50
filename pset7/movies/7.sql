SELECT title, rating FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE year = 2010
-- Descending/Ascending must be determined on each variable
ORDER BY rating DESC, title ASC;