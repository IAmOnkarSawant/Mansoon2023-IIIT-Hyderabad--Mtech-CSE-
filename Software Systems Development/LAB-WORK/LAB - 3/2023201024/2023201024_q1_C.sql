
UPDATE SSDLab.menu SET price  = (
CASE
    WHEN food_type = "veg" THEN price-1
    ELSE price-5
END
);  

select * from SSDLab.menu;