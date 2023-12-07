select * from Assignment1.Orders_table;
select * from Assignment1.laptop_brands;
select * from Assignment1.users_table;



CREATE TABLE IF NOT exists JOINED_TABLE AS 
    SELECT
        u.`User ID`,
        u.`Name`,
        u.`Favorite Laptop Brand`,
        o.`Order ID`,
        o.`Order Date`,
        o.`Brand ID` AS BID,
        o.`Buyer ID`,
        o.`Seller ID`,
        lb.`Brand ID` AS BrandID,
        lb.`Laptop Brand`
    FROM
        users_table u
    LEFT JOIN
        Orders_table o ON u.`User ID` = o.`Seller ID`
    LEFT JOIN
        laptop_brands lb ON o.`Brand ID` = lb.`Brand ID`;

select * from JOINED_TABLE;
alter table JOINED_TABLE 
modify column BID varchar(50);

UPDATE JOINED_TABLE ut
JOIN Assignment1.laptop_brands lb ON ut.BID = lb.`Brand ID`
SET ut.BID = lb.`Laptop Brand`
WHERE ut.BID IS NOT NULL;

CREATE TABLE Assignment1.report(
	UserID int,
    UserName varchar(40),
    Result varchar(5)
);
       

select * from JOINED_TABLE;

