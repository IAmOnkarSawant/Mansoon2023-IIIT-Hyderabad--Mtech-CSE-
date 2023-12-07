select title as book_name, author_name, date_issued as recent_date_issued
FROM SSDLab.authors
INNER JOIN SSDLab.books ON authors.author_id = books.author_id
RIGHT JOIN SSDLab.issued_users ON issued_users.book_id = books.book_id
where date_issued = (
select max(date_issued) 
from SSDLab.issued_users as IU 
where issued_users.book_id = IU.book_id 
group by book_id);
