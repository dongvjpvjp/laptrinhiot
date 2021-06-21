create database nhom9;
use nhom9;
ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'root';
create table sensor (tg text, noidung text); 
insert into sensor (tg,noidung) values ("1/1/1",'co anh sang');
select * from sensor;
drop table sensor;