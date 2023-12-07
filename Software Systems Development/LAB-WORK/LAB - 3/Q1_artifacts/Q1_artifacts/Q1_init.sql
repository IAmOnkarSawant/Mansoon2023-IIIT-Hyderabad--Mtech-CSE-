-- Create SSDLab database
CREATE DATABASE SSDLab;

-- Create Menu Table
CREATE TABLE SSDLab.menu (
    dish_name VARCHAR(255),
    price INT
);

-- Inserting Indian Chicken and Paneer Dishes into the Menu Table
INSERT INTO SSDLab.menu (dish_name, price) VALUES ('  00B00utter 00Chi00cken   ', 700);
INSERT INTO SSDLab.menu (dish_name, price) VALUES ('         0000Chicken T00ikka00 ', 550);
INSERT INTO SSDLab.menu (dish_name, price) VALUES ('T000000andoori Chick00en               ', 600);
INSERT INTO SSDLab.menu (dish_name, price) VALUES ('  00Chic000ken00 00Ko0r0m0a0 ', 350);
INSERT INTO SSDLab.menu (dish_name, price) VALUES ('00 00 00 Chicken 0000Biryani000', 450);
INSERT INTO SSDLab.menu (dish_name, price) VALUES ('Chicken Curry', 500);
INSERT INTO SSDLab.menu (dish_name, price) VALUES ('Paneer Tikka', 300);
INSERT INTO SSDLab.menu (dish_name, price) VALUES ('000000  0000     0Paneer Butter Masala', 550);
INSERT INTO SSDLab.menu (dish_name, price) VALUES ('     Paneer Makhani       ', 350);
INSERT INTO SSDLab.menu (dish_name, price) VALUES ('0Paneer0 0Tikka0 0Masala0', 450);
