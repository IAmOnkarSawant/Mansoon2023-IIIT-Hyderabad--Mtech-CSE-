
UPDATE SSDLab.menu SET dish_name = REPLACE(dish_name, '0', '');
UPDATE SSDLab.menu SET dish_name = TRIM(dish_name);
select * from SSDLab.menu;