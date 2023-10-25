-- Write a PL/SQL block of code using parameterized Cursor, that will merge the data available in the newly 
-- created table

create table old_roll(roll int,name varchar(10));

create table new_roll(roll int,name varchar(10));

insert into old_roll values(4,'d');
insert into old_roll values(3,'bcd');
insert into old_roll values(1,'bc');
insert into old_roll values(5,'bch');
insert into new_roll values(2,'b');
insert into new_roll values(5,'bch');
insert into new_roll values(1,'bc');

select * from old_roll;

select * from new_roll;

delimiter //
create procedure roll_list()
begin
    declare oldrollnumber int;
    declare oldname varchar(10);
    declare newrollnumber int;
    declare newname varchar(10);
    declare done int default false;
    declare c1 cursor for select roll,name from old_roll;
    declare c2 cursor for select roll,name from new_roll;
    declare continue handler for not found set done=true;
    open c1;

    loop1:loop
        fetch c1 into oldrollnumber,oldname;
        if done then
            leave loop1;
        end if;
        open c2;

        loop2:loop
            fetch c2 into newrollnumber,newname;
            if done then
                insert into new_roll values(oldrollnumber,oldname);
                set done=false;
                close c2;
                leave loop2;
            end if;
            if oldrollnumber=newrollnumber then
                leave loop2;
            end if;
        end loop;
    end loop;
        close c1;
end //
delimiter ;

call roll_list();

select * from new_roll;
