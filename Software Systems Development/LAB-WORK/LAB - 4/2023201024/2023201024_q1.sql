DELIMITER //

CREATE PROCEDURE Divide(
	IN num1 INT,
    IN num2 INT,
    OUT ans DECIMAL(15,2))
BEGIN
	IF num2 != 0 THEN
		SET ans = num1 / num2;
        select ans as ANSWER;
	ELSE
		SELECT CONCAT("Division of numbers not possible"," ","num2 is zero") as message;
	END IF;
END //

DELIMITER ;

call Divide(10, 0, @ans);
