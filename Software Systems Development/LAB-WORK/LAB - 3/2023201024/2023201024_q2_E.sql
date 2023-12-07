
select genre from SSDLab.books 
SELECT genre
FROM SSDLab.books
INNER JOIN SSDLab.issued_users ON books.book_id = issued_users.book_id 

