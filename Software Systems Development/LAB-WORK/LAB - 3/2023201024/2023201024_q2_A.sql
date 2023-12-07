SELECT user_name , title, author_name
FROM SSDLab.authors
INNER JOIN SSDLab.books ON authors.author_id = books.author_id
INNER JOIN SSDLab.issued_users ON issued_users.book_id = books.book_id
where books.title is not NULL and authors.author_name is not null;