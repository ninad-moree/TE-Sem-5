show tables;
+--------------------+
| Tables_in_31253_db |
+--------------------+
| PlacementDrive |
| Student |
| Training |
+--------------------+


select * from Student;
+-------+----------+------+-----------------+------+----------+------------+
| s_id | drive_id | t_id | s_name | CGPA | s_branch | s_dob |
+-------+----------+------+-----------------+------+----------+------------+
| 31253 | 101 | 501 | Ninad More | 9.98 | CE | 18-03-2003 |
| 31263 | 110 | 510 | Pranay Agrawal | 9.9 | CE | 25-12-2003 |
| 31262 | 104 | 504 | Peeyush Kulgude | 9.69 | CE | 07-07-2003 |
| 31254 | 108 | 508 | Karan Mundada | 9.42 | CE | 17-02-2003 |
| 31258 | 106 | 506 | Abcedf Khfh | 8.69 | IT | 09-01-2003 |
| 31255 | 105 | 505 | Reed Wise | 8.42 | IT | 17-02-2003 |
| 31261 | 102 | 502 | Xywsc Hbhw | 9.19 | IT | 30-05-2003 |
| 31256 | 103 | 503 | Ghewf Thwb | 10 | IT | 06-06-2003 |
| 31259 | 107 | 507 | Shoyo Blitz | 10 | ENTC | 01-01-2003 |
| 31260 | 109 | 509 | Ken Kaneki | 9.18 | ENTC | 04-07-2003 |
+-------+----------+------+-----------------+------+----------+------------+


select * from PlacementDrive;
+----------+---------------+-------------+----------------+
| drive_id | Pcompany_name | package_LPA | location |
+----------+---------------+-------------+----------------+
| 101 | Google | 25 | Pune |
| 110 | Microsoft | 20 | Mumbai |
| 104 | Amazon | 22 | Mumbai |
| 108 | Deutsch Bank | 21 | Banglore |
| 106 | Google | 15 | Pune |
| 105 | Barclays | 17 | Pune |
| 102 | Bajaj Finser | 17.5 | Banglore |
| 103 | Amazon | 27 | Pune |
| 107 | Microsoft | 20 | Silicon Valley |
| 109 | Flipkart | 14 | Mumbai |
+----------+---------------+-------------+----------------+


select * from Training;
+------+---------------+-------+--------+
| t_id | Tcompany_name | T_fee | T_year |
+------+---------------+-------+--------+
| 501 | Amazon | 15000 | 2020 |
| 510 | Tata | 19000 | 2021 |
| 504 | Mastercard | 14950 | 2019 |
| 508 | Tata | 23000 | 2019 |
| 506 | Google | 10000 | 2021 |
| 505 | Redhat | 17825 | 2019 |
| 502 | MMT | 12500 | 2020 |
| 503 | Amazon | 13225 | 2019 |
| 507 | Mastercard | 14950 | 2019 |
| 509 | Tata | 14000 | 2020 |
| 510 | Amazon | 12000 | 2019 |
| 503 | Google | 11000 | 2021 |
| 504 | Mastercard | 13000 | 2020 |
+------+---------------+-------+--------+


-- 1) Display all students details with branch ‘Computer ‘and ‘It’ and student name
-- starting with 'a' or 'd'.
select * from Student where (s_name like 'a%' or s_name like 'd%') and (s_branch="CE" or s_branch="IT");
+-------+----------+------+-------------+------+----------+------------+
| s_id | drive_id | t_id | s_name | CGPA | s_branch | s_dob |
+-------+----------+------+-------------+------+----------+------------+
| 31258 | 106 | 506 | Abcedf Khfh | 8.69 | IT | 09-01-2003 |
+-------+----------+------+-------------+------+----------+------------+


-- 2) List the number of different companies.(use of distinct)
select distinct(Pcompany_name) from PlacementDrive;
+---------------+
| Pcompany_name |
+---------------+
| Google |
| Microsoft |
| Amazon |
| Deutsch Bank |
| Barclays |
| Bajaj Finser |
| Flipkart |
+---------------+


-- 3) Give 15% increase in fee of the Training whose joining year is 2019.
update Training set T_fee = T_fee + (T_fee*15/100) where T_year=2019;
select * from Training;
+------+---------------+----------+--------+
| t_id | Tcompany_name | T_fee | T_year |
+------+---------------+----------+--------+
| 501 | Amazon | 15000 | 2020 |
| 510 | Tata | 19000 | 2021 |
| 504 | Mastercard | 17192.5 | 2019 |
| 508 | Tata | 26450 | 2019 |
| 506 | Google | 10000 | 2021 |
| 505 | Redhat | 20498.75 | 2019 |
| 502 | MMT | 12500 | 2020 |
| 503 | Amazon | 15208.75 | 2019 |
| 507 | Mastercard | 17192.5 | 2019 |
| 509 | Tata | 14000 | 2020 |
| 510 | Amazon | 13800 | 2019 |
| 503 | Google | 11000 | 2021 |
| 504 | Mastercard | 13000 | 2020 |
+------+---------------+----------+--------+


-- 4). Delete Student details having CGPA score less than 7.
insert into Student values(31257, 111, 511, "Hjwf GHee", 7, "IT", "09-04-2003");
select * from Student;
+-------+----------+------+-----------------+------+----------+------------+
| s_id | drive_id | t_id | s_name | CGPA | s_branch | s_dob |
+-------+----------+------+-----------------+------+----------+------------+
| 31253 | 101 | 501 | Ninad More | 9.98 | CE | 18-03-2003 |
| 31263 | 110 | 510 | Pranay Agrawal | 9.9 | CE | 25-12-2003 |
| 31262 | 104 | 504 | Peeyush Kulgude | 9.69 | CE | 07-07-2003 |
| 31254 | 108 | 508 | Karan Mundada | 9.42 | CE | 17-02-2003 |
| 31258 | 106 | 506 | Abcedf Khfh | 8.69 | IT | 09-01-2003 |
| 31255 | 105 | 505 | Reed Wise | 8.42 | IT | 17-02-2003 |
| 31261 | 102 | 502 | Xywsc Hbhw | 9.19 | IT | 30-05-2003 |
| 31256 | 103 | 503 | Ghewf Thwb | 10 | IT | 06-06-2003 |
| 31259 | 107 | 507 | Shoyo Blitz | 10 | ENTC | 01-01-2003 |
| 31260 | 109 | 509 | Ken Kaneki | 9.18 | ENTC | 04-07-2003 |
| 31257 | 111 | 511 | Hjwf GHee | 7 | IT | 09-04-2003 |
+-------+----------+------+-----------------+------+----------+------------+
delete from Student where CGPA <= 7;
select * from Student;
+-------+----------+------+-----------------+------+----------+------------+
| s_id | drive_id | t_id | s_name | CGPA | s_branch | s_dob |
+-------+----------+------+-----------------+------+----------+------------+
| 31253 | 101 | 501 | Ninad More | 9.98 | CE | 18-03-2003 |
| 31263 | 110 | 510 | Pranay Agrawal | 9.9 | CE | 25-12-2003 |
| 31262 | 104 | 504 | Peeyush Kulgude | 9.69 | CE | 07-07-2003 |
| 31254 | 108 | 508 | Karan Mundada | 9.42 | CE | 17-02-2003 |
| 31258 | 106 | 506 | Abcedf Khfh | 8.69 | IT | 09-01-2003 |
| 31255 | 105 | 505 | Reed Wise | 8.42 | IT | 17-02-2003 |
| 31261 | 102 | 502 | Xywsc Hbhw | 9.19 | IT | 30-05-2003 |
| 31256 | 103 | 503 | Ghewf Thwb | 10 | IT | 06-06-2003 |
| 31259 | 107 | 507 | Shoyo Blitz | 10 | ENTC | 01-01-2003 |
| 31260 | 109 | 509 | Ken Kaneki | 9.18 | ENTC | 04-07-2003 |
+-------+----------+------+-----------------+------+----------+------------+


-- 5) Find the names of companies belonging to pune or Mumbai
select distinct(Pcompany_name) from PlacementDrive where (location="Pune" or location="Mumbai");
+---------------+
| Pcompany_name |
+---------------+
| Google |
| Microsoft |
| Amazon |
| Barclays |
| Flipkart |
+---------------+


-- 6) Find the student name having maximum CGPA score and names of students
-- having CGPA score between 7 to 9 .
select s_name from Student where CGPA=10 or (CGPA>=7 and CGPA<=9);
+-------------+
| s_name |
+-------------+
| Abcedf Khfh |
| Reed Wise |
| Ghewf Thwb |
| Shoyo Blitz |
+-------------+


-- 7) Display all Student name with T_id with decreasing order of Fees
select s.s_name, t.t_id from Student s join Training t on s.t_id = t.t_id order by t.T_fee desc;
+-----------------+------+
| s_name | t_id |
+-----------------+------+
| Karan Mundada | 508 |
| Reed Wise | 505 |
| Pranay Agrawal | 510 |
| Peeyush Kulgude | 504 |
| Shoyo Blitz | 507 |
| Ghewf Thwb | 503 |
| Ninad More | 501 |
| Ken Kaneki | 509 |
| Pranay Agrawal | 510 |
| Peeyush Kulgude | 504 |
| Xywsc Hbhw | 502 |
| Pranay Agrawal | 510 |
| Ghewf Thwb | 503 |
| Ghewf Thwb | 503 |
| Abcedf Khfh | 506 |
+-----------------+------+


-- 8) Display PCompany name, S_name ,location and Package with Package 30K,
-- 40K and 50k
select pd.Pcompany_name, s.s_name, pd.location, pd.package_LPA from Student s join PlacementDrive pd on s.drive_id = pd.drive_id where pd.package_LPA in (20,22,25);
+---------------+-----------------+----------------+-------------+
| Pcompany_name | s_name | location | package_LPA |
+---------------+-----------------+----------------+-------------+
| Google | Ninad More | Pune | 25 |
| Microsoft | Pranay Agrawal | Mumbai | 20 |
| Amazon | Peeyush Kulgude | Mumbai | 22 |
| Microsoft | Shoyo Blitz | Silicon Valley | 20 |
+---------------+-----------------+----------------+-------------+


-- 9) Find the student name who joined training in 1-1-2019 as well as in 1-1-2021
select distinct s.s_name 
from Student s 
where s.t_id in (select  t_id from Training where T_year = 2019 ) 
and 
s.t_id in ( select t_id from Training where T_year = 2021 ) 
and  
s.t_id not in (select t_id from Training where T_year not in (2019, 2021) );
+----------------+
| s_name     	|
+----------------+
| Pranay Agrawal |
| Ghewf Thwb 	|
+----------------+
