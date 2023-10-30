-- 1. Find the Student details and Placement details using NATURAL JOIN.
select * from Student natural join PlacementDrive;
+----------+-------+------+-----------------+------+----------+------------+---------------+-------------+----------------+
| drive_id | s_id  | t_id | s_name      	| CGPA | s_branch | s_dob  	| Pcompany_name | package_LPA | location   	|
+----------+-------+------+-----------------+------+----------+------------+---------------+-------------+----------------+
|  	101 | 31253 |  501 | Ninad More  	| 9.98 | CE   	| 18-03-2003 | Google    	|      	25 | Pune       	|
|  	110 | 31263 |  510 | Pranay Agrawal  |  9.9 | CE   	| 25-12-2003 | Microsoft 	|      	20 | Mumbai     	|
|  	104 | 31262 |  504 | Peeyush Kulgude | 9.69 | CE   	| 07-07-2003 | Amazon    	|      	22 | Mumbai     	|
|  	108 | 31254 |  508 | Karan Mundada   | 9.42 | CE   	| 17-02-2003 | Deutsch Bank  |      	21 | Banglore   	|
|  	106 | 31258 |  506 | Abcedf Khfh 	| 8.69 | IT   	| 09-01-2003 | Google    	|      	15 | Pune       	|
|  	105 | 31255 |  505 | Reed Wise   	| 8.42 | IT   	| 17-02-2003 | Barclays  	|      	17 | Pune       	|
|  	102 | 31261 |  502 | Xywsc Hbhw  	| 9.19 | IT   	| 30-05-2003 | Bajaj Finser  |    	17.5 | Banglore   	|
|  	103 | 31256 |  503 | Ghewf Thwb  	|   10 | IT   	| 06-06-2003 | Amazon    	|      	27 | Pune       	|
|  	107 | 31259 |  507 | Shoyo Blitz 	|   10 | ENTC 	| 01-01-2003 | Microsoft 	|      	20 | Silicon Valley |
|  	109 | 31260 |  509 | Ken Kaneki  	| 9.18 | ENTC 	| 04-07-2003 | Flipkart  	|      	14 | Mumbai     	|
+----------+-------+------+-----------------+------+----------+------------+---------------+-------------+----------------+


-- 2. Find all the student details with company_name who have conducted in same drive
SELECT s.s_id, s.s_name, s.drive_id, GROUP_CONCAT(pd.Pcompany_name) 
AS company_names FROM Student s JOIN PlacementDrive pd 
ON s.drive_id = pd.drive_id 
GROUP BY s.drive_id, s.s_id, s.s_name;
+-------+-----------------+----------+---------------+
| s_id  | s_name      	  | drive_id | company_names |
+-------+-----------------+----------+---------------+
| 31253 | Ninad More  	  |  	101 | Google    	 |
| 31261 | Xywsc Hbhw  	  |  	102 | Bajaj Finser   |
| 31256 | Ghewf Thwb  	  |  	103 | Amazon    	 |
| 31262 | Peeyush Kulgude |  	104 | Amazon    	 |
| 31255 | Reed Wise   	  |  	105 | Barclays  	 |
| 31258 | Abcedf Khfh 	  |  	106 | Google    	 |
| 31259 | Shoyo Blitz 	  |  	107 | Microsoft 	 |
| 31254 | Karan Mundada   |  	108 | Deutsch Bank   |
| 31260 | Ken Kaneki  	  |  	109 | Flipkart  	 |
| 31263 | Pranay Agrawal  |  	110 | Microsoft 	 |
+-------+-----------------+----------+---------------+


-- 3. List all the Student name and Student branch of Student having package 5 LPA
select s.s_name, s_branch, pd.package_LPA 
from Student s join PlacementDrive pd 
on s.drive_id = pd.drive_id 
where pd.package_LPA in (20);
+----------------+----------+-------------+
| s_name     	| s_branch  | package_LPA |
+----------------+----------+-------------+
| Pranay Agrawal | CE   	|      	20    |
| Shoyo Blitz	 | ENTC 	|      	20    |
+----------------+----------+-------------+


-- 4.List all the student names ,company_name having T_fee more than 20000
select s.s_name, t.Tcompany_name,t.T_fee 
from Student s join Training t 
on s.t_id = t.t_id 
where T_fee > 20000;
+---------------+---------------+----------+
| s_name    	| Tcompany_name | T_fee	   |
+---------------+---------------+----------+
| Karan Mundada | Tata      	|	26450  |
| Reed Wise 	| Redhat    	| 20498.75 |
+---------------+---------------+----------+


-- 5. Display all training details attended by ‘ninad” in year 2020.
select s.s_name, t.* 
from Student s join Training t 
on s.t_id = t.t_id 
where s_name="Ninad More" and T_year=2020;
+------------+------+---------------+-------+--------+
| s_name 	| t_id | Tcompany_name | T_fee | T_year  |
+------------+------+---------------+-------+--------+
| Ninad More |  501 | Amazon    	| 15000 |   2020 |
+------------+------+---------------+-------+--------+


-- 6. list the total number of companies who conduct training before 2021.
select * from Training where T_year < 2021;
+------+---------------+----------+--------+
| t_id | Tcompany_name | T_fee	| T_year |
+------+---------------+----------+--------+
|  501 | Amazon    	|	15000 |   2020 |
|  504 | Mastercard	|  17192.5 |   2019 |
|  508 | Tata      	|	26450 |   2019 |
|  505 | Redhat    	| 20498.75 |   2019 |
|  502 | MMT       	|	12500 |   2020 |
|  503 | Amazon    	| 15208.75 |   2019 |
|  507 | Mastercard	|  17192.5 |   2019 |
|  509 | Tata      	|	14000 |   2020 |
|  510 | Amazon    	|	13800 |   2019 |
|  504 | Mastercard	|	13000 |   2020 |
|  510 | Amazon    	|	12000 |   2019 |
+------+---------------+----------+--------+


-- 7. List the students name with company ‘Microsoft’ and location ’Thane’.
select s.s_name, p.Pcompany_name, p.location 
from Student s join PlacementDrive p 
on s.drive_id = p.drive_id 
where Pcompany_name = "Amazon" and location = "Pune";
+------------+---------------+----------+
| s_name 	| Pcompany_name | location |
+------------+---------------+----------+
| Ghewf Thwb | Amazon    	| Pune 	|
+------------+---------------+----------+


-- 8. Find the names of all Students who have joined ‘Microsoft ‘ training in 2015 .
select s.s_name, t.Tcompany_name, t.T_year 
from Student s join Training t 
on s.t_id = t.t_id 
where Tcompany_name="Amazon" and T_year=2020;
+------------+---------------+--------+
| s_name 	| Tcompany_name | T_year |
+------------+---------------+--------+
| Ninad More | Amazon    	|   2020 |
+------------+---------------+--------+


-- 9. Create a view showing the Student and Training details.
create view StuTrain as select * from Student natural join Training;

select * from StuTrain;
+------+-------+----------+-----------------+------+----------+------------+---------------+----------+--------+
| t_id | s_id  | drive_id | s_name      	| CGPA | s_branch | s_dob  	| Tcompany_name | T_fee	| T_year |
+------+-------+----------+-----------------+------+----------+------------+---------------+----------+--------+
|  501 | 31253 |  	101 | Ninad More  	| 9.98 | CE   	| 18-03-2003 | Amazon    	|	15000 |   2020 |
|  510 | 31263 |  	110 | Pranay Agrawal  |  9.9 | CE   	| 25-12-2003 | Tata      	|	19000 |   2021 |
|  504 | 31262 |  	104 | Peeyush Kulgude | 9.69 | CE   	| 07-07-2003 | Mastercard	|  17192.5 |   2019 |
|  508 | 31254 |  	108 | Karan Mundada   | 9.42 | CE   	| 17-02-2003 | Tata      	|	26450 |   2019 |
|  506 | 31258 |  	106 | Abcedf Khfh 	| 8.69 | IT   	| 09-01-2003 | Google    	|	10000 |   2021 |
|  505 | 31255 |  	105 | Reed Wise   	| 8.42 | IT   	| 17-02-2003 | Redhat    	| 20498.75 |   2019 |
|  502 | 31261 |  	102 | Xywsc Hbhw  	| 9.19 | IT   	| 30-05-2003 | MMT       	|	12500 |   2020 |
|  503 | 31256 |  	103 | Ghewf Thwb  	|   10 | IT   	| 06-06-2003 | Amazon    	| 15208.75 |   2019 |
|  507 | 31259 |  	107 | Shoyo Blitz 	|   10 | ENTC 	| 01-01-2003 | Mastercard	|  17192.5 |   2019 |
|  509 | 31260 |  	109 | Ken Kaneki  	| 9.18 | ENTC 	| 04-07-2003 | Tata      	|	14000 |   2020 |
|  510 | 31263 |  	110 | Pranay Agrawal  |  9.9 | CE   	| 25-12-2003 | Amazon    	|	13800 |   2019 |
|  503 | 31256 |  	103 | Ghewf Thwb  	|   10 | IT   	| 06-06-2003 | Google    	|	11000 |   2021 |
|  504 | 31262 |  	104 | Peeyush Kulgude | 9.69 | CE   	| 07-07-2003 | Mastercard	|	13000 |   2020 |
|  510 | 31263 |  	110 | Pranay Agrawal  |  9.9 | CE   	| 25-12-2003 | Amazon    	|	12000 |   2019 |
|  503 | 31256 |  	103 | Ghewf Thwb  	|   10 | IT   	| 06-06-2003 | Google    	|	11000 |   2021 |
+------+-------+----------+-----------------+------+----------+------------+---------------+----------+--------+


-- 10. Perform Manipulation on simple view-Insert, update, delete, drop view.
create view SimpleView as select s_id,s_name,CGPA from Student;
+-------+-----------------+------+
| s_id  | s_name      	| CGPA |
+-------+-----------------+------+
| 31253 | Ninad More  	| 9.98 |
| 31263 | Pranay Agrawal  |  9.9 |
| 31262 | Peeyush Kulgude | 9.69 |
| 31254 | Karan Mundada   | 9.42 |
| 31258 | Abcedf Khfh 	| 8.69 |
| 31255 | Reed Wise   	| 8.42 |
| 31261 | Xywsc Hbhw  	| 9.19 |
| 31256 | Ghewf Thwb  	|   10 |
| 31259 | Shoyo Blitz 	|   10 |
| 31260 | Ken Kaneki  	| 9.18 |
| 31209 | Sukuna      	| 8.69 |
+-------+-----------------+------+

-- Insertion:
insert into SimpleView values(31201,"Eren",7.69);

select * from SimpleView;
+-------+-----------------+------+
| s_id  | s_name      	| CGPA |
+-------+-----------------+------+
| 31253 | Ninad More  	| 9.98 |
| 31263 | Pranay Agrawal  |  9.9 |
| 31262 | Peeyush Kulgude | 9.69 |
| 31254 | Karan Mundada   | 9.42 |
| 31258 | Abcedf Khfh 	| 8.69 |
| 31255 | Reed Wise   	| 8.42 |
| 31261 | Xywsc Hbhw  	| 9.19 |
| 31256 | Ghewf Thwb  	|   10 |
| 31259 | Shoyo Blitz 	|   10 |
| 31260 | Ken Kaneki  	| 9.18 |
| 31209 | Sukuna      	| 8.69 |
| 31201 | Eren        	| 7.69 |
+-------+-----------------+------+

-- Update:
update SimpleView set CGPA=8.99 where S_name="Eren";

select * from SimpleView;
+-------+-----------------+------+
| s_id  | s_name      	| CGPA |
+-------+-----------------+------+
| 31253 | Ninad More  	| 9.98 |
| 31263 | Pranay Agrawal  |  9.9 |
| 31262 | Peeyush Kulgude | 9.69 |
| 31254 | Karan Mundada   | 9.42 |
| 31258 | Abcedf Khfh 	| 8.69 |
| 31255 | Reed Wise   	| 8.42 |
| 31261 | Xywsc Hbhw  	| 9.19 |
| 31256 | Ghewf Thwb  	|   10 |
| 31259 | Shoyo Blitz 	|   10 |
| 31260 | Ken Kaneki  	| 9.18 |
| 31209 | Sukuna      	| 8.69 |
| 31201 | Eren        	| 8.99 |
+-------+-----------------+------+
