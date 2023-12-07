
select food_type, avg(price) as avg_food_type from SSDLab.menu
group by food_type 
having avg(price) > 400
order by avg(price) desc;

select * from SSDLab.menu;