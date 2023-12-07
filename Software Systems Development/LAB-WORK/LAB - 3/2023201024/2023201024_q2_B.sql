select genre, count(user_id) as total_user_count 
from SSDLab.books 
inner join SSDLab.issued_users on books.book_id = issued_users.book_id
group by genre;