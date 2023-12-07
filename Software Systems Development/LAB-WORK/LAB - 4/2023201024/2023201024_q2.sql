DELIMITER //

CREATE PROCEDURE getData(
    IN payment INT)
BEGIN
	select CUST_NAME, CUST_CITY from CUSTOMER_DB.customer 
    where PAYMENT_AMT > payment;
END //

DELIMITER ;

call getData(5000);
