-- Create authors table
CREATE TABLE SSDLab.authors (
	author_id int,
    author_name varchar(30)
);

-- Create books table
CREATE TABLE SSDLab.books (
	book_id int,
    title varchar(100),
    author_id int,
    genre varchar(20)
);

-- Create issued_users table
CREATE TABLE SSDLab.issued_users (
	user_id int,
    user_name varchar(20),
    book_id int,
    date_issued date
);


-- Inserting Data into the Authors Table
INSERT INTO SSDLab.authors (author_id, author_name) VALUES (1, 'Arundhati Roy');
INSERT INTO SSDLab.authors (author_id, author_name) VALUES (2, 'Chetan Bhagat');
INSERT INTO SSDLab.authors (author_id, author_name) VALUES (3, 'Amish Tripathi');
INSERT INTO SSDLab.authors (author_id, author_name) VALUES (4, 'Jhumpa Lahiri');
INSERT INTO SSDLab.authors (author_id, author_name) VALUES (5, 'Vikram Seth');
INSERT INTO SSDLab.authors (author_id, author_name) VALUES (6, 'Ruskin Bond');
INSERT INTO SSDLab.authors (author_id, author_name) VALUES (7, 'Ravinder Singh');
INSERT INTO SSDLab.authors (author_id, author_name) VALUES (8, 'Anita Desai');
INSERT INTO SSDLab.authors (author_id, author_name) VALUES (9, 'Salman Rushdie');
INSERT INTO SSDLab.authors (author_id, author_name) VALUES (10, 'Shashi Tharoor');
INSERT INTO SSDLab.authors (author_id) VALUES (11);
INSERT INTO SSDLab.authors (author_id, author_name) VALUES (12, 'Aravind Adiga');


-- Inserting Data into the Books Table
INSERT INTO SSDLab.books (book_id, title, author_id, genre) VALUES (1, 'The God of Small Things', 1, 'Fiction');
INSERT INTO SSDLab.books (book_id, title, author_id, genre) VALUES (2, 'Revolution 2020', 2, 'Romance');
INSERT INTO SSDLab.books (book_id, title, author_id, genre) VALUES (3, 'Half Girlfriend', 2, 'Romance');
INSERT INTO SSDLab.books (book_id, title, author_id, genre) VALUES (4, 'The Secret of the Nagas', 3, 'Mythology');
INSERT INTO SSDLab.books (book_id, title, author_id, genre) VALUES (5, 'The Oath of the Vayuputras', 3, 'Mythology');
INSERT INTO SSDLab.books (book_id, title, author_id, genre) VALUES (6, 'Interpreter of Maladies', 4, 'Fiction');
INSERT INTO SSDLab.books (book_id, title, author_id, genre) VALUES (7, 'Unaccustomed Earth', 4, 'Fiction');
INSERT INTO SSDLab.books (book_id, title, author_id, genre) VALUES (8, 'Beastly Tales from Here and There', 5, 'Fantasy');
INSERT INTO SSDLab.books (book_id, title, author_id, genre) VALUES (9, 'Rusty and the Magic Mountain', 6, 'Children');
INSERT INTO SSDLab.books (book_id, title, author_id, genre) VALUES (10, 'The Cherry Tree', 6, 'Children');
INSERT INTO SSDLab.books (book_id, title, author_id, genre) VALUES (11, 'This Love That Feels Right', 17, 'Romance');
INSERT INTO SSDLab.books (book_id, author_id, genre) VALUES (12, 8, 'Fiction');
INSERT INTO SSDLab.books (book_id, title, author_id, genre) VALUES (13, 'In Custody', 8, 'Fiction');
INSERT INTO SSDLab.books (book_id, title, author_id, genre) VALUES (14, 'Haroun and the Sea of Stories', 9, 'Fantasy');
INSERT INTO SSDLab.books (book_id, title, author_id, genre) VALUES (15, 'The Satanic Verses', 9, 'Fiction');
INSERT INTO SSDLab.books (book_id, title, author_id, genre) VALUES (16, 'Riot: A Love Story', 10, 'Fiction');
INSERT INTO SSDLab.books (book_id, title, author_id, genre) VALUES (17, 'Why I Am a Hindu', 10, 'Non-Fiction');
INSERT INTO SSDLab.books (book_id, title, author_id, genre) VALUES (18, 'The White Tiger', 11, 'Fiction');


-- Inserting Data into the Issued Users Table
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (4, 'Priya', 1, '2023-07-15');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (7, 'Kavya', 1, '2023-07-20');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (5, 'Neha', 2, '2023-08-02');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (11, 'Arjun', 2, '2023-07-24');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (17, 'Aryan', 2, '2023-08-03');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (2, 'Simran', 3, '2023-08-17');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (6, 'Vikrant', 3, '2023-07-18');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (2, 'Simran', 4, '2023-08-02');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (6, 'Vikrant', 4, '2023-08-15');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (3, 'Karan', 5, '2023-07-12');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (9, 'Isha', 5, '2023-08-11');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (7, 'Kavya', 6, '2023-08-09');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (8, 'Aarav', 6, '2023-07-22');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (11, 'Arjun', 6, '2023-07-25');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (12, 'Vivan', 7, '2023-08-05');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (11, 'Arjun', 7, '2023-08-03');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (1, 'Aditi', 8, '2023-08-10');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (14, 'Anika', 8, '2023-08-01');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (13, 'Aanya', 9, '2023-08-08');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (15, 'Kabir', 11, '2023-07-26');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (16, 'Sanjay', 11, '2023-07-25');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (1, 'Aditi', 12, '2023-08-05');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (6, 'Vikrant', 12, '2023-08-01');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (16, 'Sanjay', 13, '2023-03-27');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (17, 'Aryan', 13, '2023-08-08');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (18, 'Riya', 14, '2023-07-20');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (15, 'Kabir', 14, '2023-07-30');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (10, 'Tanvi', 15, '2023-07-25');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (7, 'Kavya', 15, '2023-08-06');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (15, 'Kabir', 16, '2023-07-28');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (9, 'Isha', 16, '2023-08-10');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (18, 'Riya', 17, '2023-07-09');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (15, 'Kabir', 17, '2023-07-18');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (12, 'Vivan', 18, '2023-08-08');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (13, 'Aanya', 28, '2023-08-12');
INSERT INTO SSDLab.issued_users (user_id, user_name, book_id, date_issued) VALUES (14, 'Anika', 28, '2023-07-20');
