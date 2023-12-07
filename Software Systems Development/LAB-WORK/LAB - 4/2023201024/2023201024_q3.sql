
CREATE TABLE IF NOT EXISTS CUSTOMER_DB.output_q3 (
  `CUST_NAME` varchar(40) NOT NULL,
  `CUST_COUNTRY` varchar(20) NOT NULL,
  `GRADE` decimal(10, 0) DEFAULT NULL
);

TRUNCATE TABLE CUSTOMER_DB.output_q3;


DELIMITER //

CREATE PROCEDURE getDetails()
BEGIN
    DECLARE done INT DEFAULT FALSE;
    DECLARE v_CUST_NAME varchar(40);
    DECLARE v_CUST_COUNTRY varchar(20);
    DECLARE v_GRADE decimal(10, 0); 
    DECLARE v_AGENT_CODE varchar(40);
    DECLARE getdet CURSOR FOR
    SELECT CUST_NAME, CUST_COUNTRY, GRADE FROM CUSTOMER_DB.customer
    WHERE AGENT_CODE LIKE 'A00%';

    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
	open getdet;
    lable_loop: LOOP
        FETCH getdet INTO v_CUST_NAME, v_CUST_COUNTRY, v_GRADE;
        IF (done) THEN
            LEAVE lable_loop;
        END IF;

        INSERT INTO CUSTOMER_DB.output_q3 (`CUST_NAME`, `CUST_COUNTRY`, `GRADE`)
        VALUES (v_CUST_NAME, v_CUST_COUNTRY, v_GRADE);

    END LOOP lable_loop;
END //

DELIMITER ;

CALL getDetails();
select * from CUSTOMER_DB.output_q3;
drop table CUSTOMER_DB.output_q3;