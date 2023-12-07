drop table if exists Assignment1.Employee;
drop table if exists Assignment1.Courses;
drop table if exists Assignment1.Certifications;
drop table if exists Assignment1.CourseCompletions;
drop table if exists Assignment1.CertificateCompletions;
drop table if exists Assignment1.UpdatedEmpSkills;

CREATE TABLE Assignment1.Employee(
	emp_no int,
    emp_name varchar(20),
    emp_joining_date date,
    emp_salary int
);

CREATE TABLE Assignment1.CourseCompletions(
	course_id varchar(10),
    emp_no int,
    date_completed date
);

CREATE TABLE Assignment1.CertificateCompletions(
	cert_id varchar(10),
    emp_no int,
    date_completed date
);

CREATE TABLE Assignment1.Courses(
	course_id varchar(10),
    course_name varchar(50)
);

CREATE TABLE Assignment1.Certifications(
	cert_id varchar(10),
    cert_name varchar(50)
);

CREATE TABLE Assignment1.UpdatedEmpSkills(
	emp_no int,
    curr_salary int,
    increment int,
    new_salary int,
    skill_level varchar(15)
);
-- --------------------------------------------------------------------------------------
-- 		Loading the data from csv files
-- ---------------------------------------------------------------------------------------
LOAD DATA LOCAL INFILE '/home/spartan/2023201024_A1/Question\ 4/Employee.csv'
INTO TABLE Assignment1.Employee
FIELDS TERMINATED BY ','
LINES TERMINATED BY '\n'
IGNORE 1 LINES
(emp_no, emp_name, @emp_joining_date, emp_salary) 
SET emp_joining_date = STR_TO_DATE(@emp_joining_date, '%d-%m-%Y');



-- ---------------------------------------------------------------------------------------

LOAD DATA LOCAL INFILE '/home/spartan/2023201024_A1/Question\ 4/Courses.csv'
INTO TABLE Assignment1.Courses
FIELDS TERMINATED BY ','
LINES TERMINATED BY '\n'
IGNORE 1 LINES
(course_id, course_name); 



-- ---------------------------------------------------------------------------------------

LOAD DATA LOCAL INFILE '/home/spartan/2023201024_A1/Question\ 4/Certifications.csv'
INTO TABLE Assignment1.Certifications
FIELDS TERMINATED BY ','
LINES TERMINATED BY '\n'
IGNORE 1 LINES;


-- ---------------------------------------------------------------------------------------

LOAD DATA LOCAL INFILE '/home/spartan/2023201024_A1/Question\ 4/CourseCompletions.csv'
INTO TABLE Assignment1.CourseCompletions
FIELDS TERMINATED BY ','
LINES TERMINATED BY '\n'
IGNORE 1 LINES
(course_id, emp_no, @date_completed) 
SET date_completed = STR_TO_DATE(@date_completed, '%d-%m-%Y');

-- ----------------------------------------------------------------------------------------

LOAD DATA LOCAL INFILE '/home/spartan/2023201024_A1/Question\ 4/CertificateCompletions.csv'
INTO TABLE Assignment1.CertificateCompletions
FIELDS TERMINATED BY ','
LINES TERMINATED BY '\n'
IGNORE 1 LINES
(cert_id, emp_no, @date_completed)
SET date_completed = STR_TO_DATE(@date_completed, '%d-%m-%Y');



-- -----------------------------------------------------------------------------------------
--                        CALLING THE STORED PROCEDURE
-- -----------------------------------------------------------------------------------------

 

truncate table Assignment1.UpdatedEmpSkills;
DROP PROCEDURE IF EXISTS `Increment_sal`; 
DELIMITER //
CREATE PROCEDURE `Increment_sal`()
BEGIN
    DECLARE done INT DEFAULT FALSE;
    DECLARE emp_no1 INT;
    DECLARE curr_salary1 INT;
    DECLARE cert_count1 INT;
    DECLARE course_count1 INT;
    DECLARE emp_joining_date1 date;
    DECLARE increment1 INT;
    DECLARE new_salary1 INT;
    DECLARE skill_level1 VARCHAR(15);
    
    DECLARE get_emp CURSOR FOR
        SELECT E.emp_no, E.emp_salary, CC.cert_count, C.course_count 
		FROM Employee AS E
		LEFT JOIN ( SELECT emp_no, COUNT(course_id) AS course_count
                    FROM CourseCompletions
				    GROUP BY emp_no) AS C ON E.emp_no = C.emp_no
		LEFT JOIN ( SELECT emp_no, COUNT(cert_id) AS cert_count
                    FROM CertificateCompletions
                    GROUP BY emp_no) AS CC ON E.emp_no = CC.emp_no
		WHERE E.emp_joining_date <= '2022-07-31';
    
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
	-- debug
	-- CREATE TEMPORARY TABLE debug_message (message varchar(255));
        
    OPEN get_emp;
    read_loop: LOOP
    
        FETCH get_emp INTO emp_no1, curr_salary1, cert_count1, course_count1;
        -- debug
        -- insert INTO debug_message (MESSAGE) VALUES (emp_no1);
        
        IF (done) THEN
            LEAVE read_loop;
        END IF;
        
        -- debug
        -- insert INTO debug_message (MESSAGE) VALUES (emp_no1);
        IF course_count1 >= 10 AND cert_count1 >= 8 THEN
            SET skill_level1 = "Expert";
            SET increment1 = 25;
        ELSEIF course_count1 >= 6 AND cert_count1 >= 6 THEN
            SET skill_level1 = "Advanced";
            SET increment1 = 20;
		ELSEIF course_count1 >= 4 AND cert_count1 >= 4 THEN
            SET skill_level1 = "Intermediate"; 
            SET increment1 = 15;
		ELSEIF course_count1 >= 2 AND cert_count1 >= 2 THEN
            SET skill_level1 = "Beginner"; 
            SET increment1 = 10;
		ELSE 
			SET skill_level1 = NULL;
            SET increment1 = NULL;
            SET new_salary1 = NULL;
        END IF;
        
        SET new_salary1 = curr_salary1 * ((100 + increment1)/100);
        
        INSERT INTO Assignment1.UpdatedEmpSkills 
        (emp_no, curr_salary, increment, new_salary, skill_level)
        VALUES (emp_no1, curr_salary1, increment1, new_salary1, skill_level1);
        
    END LOOP;
    
	-- SELECT * FROM debug_message;
    -- DROP TEMPORARY TABLE debug_message;
    CLOSE get_emp ;
END;
//
DELIMITER ;

CALL Increment_sal();
select * from Assignment1.UpdatedEmpSkills;
