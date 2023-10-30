-- Write a Stored Procedure namely proc_Grade for the categorization of student. If marks scored by 
-- students in examination is <=1500 and marks>=990 then student will be placed in distinction category
--  if marks scored are between 989 and900 category is first class, if marks 899 and 825 category is 
--  Higher Second Class.

CREATE TABLE stud_marks(
	name VARCHAR(50),
	total_marks INT
);

CREATE TABLE result (
	roll INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
	class VARCHAR(25) DEFAULT NULL,
	name VARCHAR(50)
);

INSERT INTO Students VALUES ('ABC', 1000);
INSERT INTO Students VALUES ('DEF', 969);
INSERT INTO Students VALUES ('GHK', 869);
INSERT INTO Students VALUES ('LMN', 1200);
INSERT INTO Students VALUES ('TUV', 920);

DELIMITER //
CREATE PROCEDURE proc_grade (IN studmarks INT, IN name VARCHAR(50), IN roll INT)
BEGIN
	DECLARE clss VARCHAR(25);
	IF studmarks BETWEEN 990 AND 1500 THEN
		SET clss := 'Distinction';
	ELSEIF studmarks BETWEEN 900 AND 989 THEN
		SET clss := 'First Class';
	ELSEIF studmarks BETWEEN 825 AND 899 THEN
		SET clss := 'Higher Second Class';
	ELSE
		SET clss := 'Pass';
	END IF;
	INSERT INTO result VALUES (roll, clss, name);
END //
DELIMITER ;

CALL proc_grade(900, 'ABC', 1);
CALL proc_grade(1000, 'DEF', 2);
CALL proc_grade(1490, 'GHK', 3);
CALL proc_grade(799, 'Durvesh', 4);
CALL proc_grade(750, 'LMN', 5);
CALL proc_grade(869, 'TUV', 6);

SELECT * FROM result;
