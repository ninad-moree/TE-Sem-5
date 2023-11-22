-- //BEFORE UPDATE
create trigger update_trigger
before update on Library
for each row
insert into Library_Audit (book_id,book_name,date_of_issue,bstatus) values (OLD.bid,OLD.bname,OLD.doi,OLD.status);

-- //AFTER UPDATE
create trigger update_trigger1
after update on Library
for each row
insert into Library_Audit values(OLD.bid,OLD.bname,new.bname,OLD.doi,OLD.status);

-- //before delete
create trigger t1
before delete on Library
for each row
insert into Library_Audit (book_id,book_name,date_of_issue,bstatus) values (OLD.bid,OLD.bname,OLD.doi,OLD.status);

-- //after delete
create trigger t2
after delete on Library
for each row
insert into Library_Audit (book_id,book_name,date_of_issue,bstatus) values (OLD.bid,OLD.bname,OLD.doi,OLD.status);

-- Insert trigger
delimiter //
create trigger t3
    -> before insert 
    -> on Library 
    -> for each row 
    -> begin
    ->     if new.bname LIKE '1%' then
    ->         signal sqlstate '45000' set message_text='INCORRECT NAME';
    ->     end if;
    -> end //


update Library set bname='Othello' where bid=2;
select * from Library_Audit;
+---------+-----------+-----------+---------------+---------+
| book_id | book_name | new_bname | date_of_issue | bstatus |
+---------+-----------+-----------+---------------+---------+
|       2 | Macbeth   | NULL      | 2023-09-05    | I       |
+---------+-----------+-----------+---------------+---------+


select * from Library;
+------+--------------+------------+--------+
| bid  | bname        | doi        | status |
+------+--------------+------------+--------+
|    1 | Matilda      | 2023-09-10 | I      |
|    2 | Othello      | 2023-09-05 | I      |
|    3 | Harry Potter | 2023-09-05 | I      |
+------+--------------+------------+--------+


update Library set bname='Percy' where bid=1;

select * from Library;
+------+--------------+------------+--------+
| bid  | bname        | doi        | status |
+------+--------------+------------+--------+
|    1 | Percy        | 2023-09-10 | I      |
|    2 | Othello      | 2023-09-05 | I      |
|    3 | Harry Potter | 2023-09-05 | I      |
+------+--------------+------------+--------+

select * from Library_Audit;
+---------+-----------+-----------+---------------+---------+
| book_id | book_name | new_bname | date_of_issue | bstatus |
+---------+-----------+-----------+---------------+---------+
|       2 | Macbeth   | NULL      | 2023-09-05    | I       |
|       1 | Matilda   | NULL      | 2023-09-10    | I       |
|       1 | Matilda   | Percy     | 2023-09-10    | I       |
+---------+-----------+-----------+---------------+---------+
