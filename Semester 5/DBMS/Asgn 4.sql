-- 1. Check the number of days (from date of issue), if days are between 15 to 30 then fine will be Rs 5 per 
-- day. If no. of days > 30, per day fine will be Rs 50 per day &amp; for days less than 30, Rs. 5 per day. 
-- After submitting the book, status will change from I to R. If the condition of fine is true, then details 
-- will be stored into the fine table.

Borrower = B
Fine = F;

select*from B;
+------+-------------------+------------+---------------------------+--------+
| roll | name              | idate      | book                      | status |
+------+-------------------+------------+---------------------------+--------+
|  201 | Rahul Sharma      | 2023-08-10 | The God of Small Things   | I      |
|  202 | Priya Patel       | 2023-08-09 | Midnights Children        | I      |
|  203 | Amit Kumar        | 2023-08-08 | The Namesake              | I      |
|  204 | Sneha Gupta       | 2023-08-07 | A Suitable Boy            | I      |
|  205 | Rajiv Verma       | 2023-08-06 | Interpreter of Maladies   | I      |
|  206 | Anjali Singh      | 2023-08-05 | The White Tiger           | I      |
|  207 | Vikram Chatterjee | 2023-08-04 | Train to Pakistan         | I      |
|  208 | Neha Sharma       | 2023-08-03 | Inheritance of Loss       | I      |
|  209 | Arun Khanna       | 2023-08-02 | The Inscrutable Americans | I      |
|  210 | Meera Patel       | 2023-08-01 | Shantaram                 | I      |
+------+-------------------+------------+---------------------------+--------+

describe F;
+-------+------+------+-----+---------+-------+
| Field | Type | Null | Key | Default | Extra |
+-------+------+------+-----+---------+-------+
| roll  | int  | YES  | MUL | NULL    |       |
| rdate | date | YES  |     | NULL    |       |
| amt   | int  | YES  |     | NULL    |       |
+-------+------+------+-----+---------+-------+


delimiter //
CREATE PROCEDURE GetInfo2(IN roll_input INT, IN date_input DATE)
    -> BEGIN
    ->     DECLARE issue_date DATE;
    ->     DECLARE temp INT;
    ->     DECLARE amount INT;
    ->
    ->     DECLARE Book_Exception CONDITION FOR SQLSTATE '45000';
    ->
    ->     SELECT idate INTO issue_date FROM B WHERE roll = roll_input;
    ->     SET temp = DATEDIFF(date_input, issue_date);
    ->
    ->     IF roll_input < 201 OR roll_input > 210 THEN
    ->         SIGNAL Book_Exception SET MESSAGE_TEXT = 'Enter valid roll number!';
    ->     END IF;
    ->
    ->     IF temp >= 15 AND temp <= 30 THEN
    ->         SET amount = temp * 5;
    ->     ELSE
    ->         SET amount = temp * 50;
    ->     END IF;
    ->
    ->     INSERT INTO F (roll, rdate, amt) VALUES (roll_input, issue_date, amount);
    ->     UPDATE B SET status = 'R' WHERE roll = roll_input;
    ->
    ->     SELECT 'Fine calculated and borrower status updated' AS Message;
    -> END;
    -> //

call GetInfo2(201, '2023-08-20');
+---------------------------------------------+
| Message                                     |
+---------------------------------------------+
| Fine calculated and borrower status updated |
+---------------------------------------------+


select*from B;
+------+-------------------+------------+---------------------------+--------+
| roll | name              | idate      | book                      | status |
+------+-------------------+------------+---------------------------+--------+
|  201 | Rahul Sharma      | 2023-08-10 | The God of Small Things   | R      |
|  202 | Priya Patel       | 2023-08-09 | Midnights Children        | I      |
|  203 | Amit Kumar        | 2023-08-08 | The Namesake              | I      |
|  204 | Sneha Gupta       | 2023-08-07 | A Suitable Boy            | I      |
|  205 | Rajiv Verma       | 2023-08-06 | Interpreter of Maladies   | I      |
|  206 | Anjali Singh      | 2023-08-05 | The White Tiger           | I      |
|  207 | Vikram Chatterjee | 2023-08-04 | Train to Pakistan         | I      |
|  208 | Neha Sharma       | 2023-08-03 | Inheritance of Loss       | I      |
|  209 | Arun Khanna       | 2023-08-02 | The Inscrutable Americans | I      |
|  210 | Meera Patel       | 2023-08-01 | Shantaram                 | I      |
+------+-------------------+------------+---------------------------+--------+


select*from F;
+------+------------+------+
| roll | rdate      | amt  |
+------+------------+------+
|  201 | 2023-08-10 |  500 |
+------+------------+------+

call GetInfo2(230, '2023-08-20');
ERROR 1644 (45000): Enter valid roll number!

call GetInfo2(205, '2023-08-30');
+---------------------------------------------+
| Message                                     |
+---------------------------------------------+
| Fine calculated and borrower status updated |
+---------------------------------------------+


select*from B;
+------+-------------------+------------+---------------------------+--------+
| roll | name              | idate      | book                      | status |
+------+-------------------+------------+---------------------------+--------+
|  201 | Rahul Sharma      | 2023-08-10 | The God of Small Things   | R      |
|  202 | Priya Patel       | 2023-08-09 | Midnights Children        | I      |
|  203 | Amit Kumar        | 2023-08-08 | The Namesake              | I      |
|  204 | Sneha Gupta       | 2023-08-07 | A Suitable Boy            | I      |
|  205 | Rajiv Verma       | 2023-08-06 | Interpreter of Maladies   | R      |
|  206 | Anjali Singh      | 2023-08-05 | The White Tiger           | I      |
|  207 | Vikram Chatterjee | 2023-08-04 | Train to Pakistan         | I      |
|  208 | Neha Sharma       | 2023-08-03 | Inheritance of Loss       | I      |
|  209 | Arun Khanna       | 2023-08-02 | The Inscrutable Americans | I      |
|  210 | Meera Patel       | 2023-08-01 | Shantaram                 | I      |
+------+-------------------+------------+---------------------------+--------+

select*from F;
+------+------------+------+
| roll | rdate      | amt  |
+------+------------+------+
|  201 | 2023-08-10 |  500 |
|  205 | 2023-08-06 |  120 |
+------+------------+------+
