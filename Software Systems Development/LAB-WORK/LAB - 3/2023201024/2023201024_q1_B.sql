
ALTER TABLE SSDLab.menu 
ADD food_type varchar(10);

UPDATE SSDLab.menu SET food_type  = (
CASE
    WHEN dish_name like '%Chicken%' THEN "non-Veg"
    ELSE "Veg" 
END
);  

select * from SSDLab.menu;