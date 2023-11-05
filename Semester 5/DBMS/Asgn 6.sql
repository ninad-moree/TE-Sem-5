create table T1(roll int, name varchar(25));
create table T2(roll int, name varchar(25));

insert into T1 values(1, 'abc');
insert into T1 values(2, 'def');
insert into T1 values(3, 'ghk');
insert into T1 values(4, 'lmn');

insert into T2 values(1, 'abc');
insert into T2 values(3, 'ghk');
insert into T2 values(5, 'tuv');

select * from T1;
select * from T2;

DELIMITER //
create procedure TRoll()
begin
    declare oldr int;
    declare newr int;
    declare oldn varchar(25);
    declare newn varchar(25);

    declare done int default false;

    declare c1 cursor for select name, roll from T1;
    declare c2 cursor for select name, roll from T2;

    declare continue handler for not found set done = true;

    open c1;
    loop1: loop
        fetch c1 into oldn, oldr;
        if done then
            leave loop1;
        end if;

        open c2;
        loop2: loop
            fetch c2 into newn, newr;
            if done then
                insert into T2 values(oldr, oldn);
                set done = false;
                close c2;
                leave loop2;
            end if;
            if oldr = newr then
                close c2;
                leave loop2;
            end if;
        end loop;
    end loop;
    close c1;
end//
DELIMITER ;

call TRoll();
