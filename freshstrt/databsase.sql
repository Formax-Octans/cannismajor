CREATE USER user12@localhost IDENTIFIED BY '34klq*';



DROP DATABASE nimbus;

DROP TABLE UserDB;

DROP TABLE FileDB;

CREATE DATABASE nimbus;
GRANT ALL ON nimbus.* to user12@localhost;

USE nimbus;

CREATE TABLE UserDB (
 uid INT AUTO_INCREMENT,
 Username varchar(100) NOT NULL UNIQUE,
 Password varchar(100) NOT NULL,
 Memory_left double NOT NULL,
 PRIMARY KEY (uid)
);


CREATE TABLE FileDB (
 pid INT AUTO_INCREMENT,
 Filename varchar(255) NOT NULL UNIQUE,
 Size double NOT NULL,
 uid int,
 Flag int,
 Fileptr varchar(255),
 PRIMARY KEY (pid),
 FOREIGN KEY (uid) REFERENCES UserDB(uid)
);



INSERT INTO UserDB VALUES (1,'Brosh_21','Birth12',900.3);
INSERT INTO UserDB VALUES (2,'Hibba969','Zetsubousei1=1',1500.3);
INSERT INTO UserDB VALUES (3,'Brosh_Hiba','Birthd12',400.31);
INSERT INTO UserDB VALUES (4,'henait_joseph','Bsadfirth12',200.34);
INSERT INTO UserDB VALUES (5,'Brosh21','Birsdafth12',204.13);




INSERT INTO FileDB VALUES (1,"1.txt",45.08,NULL,0,"1.txt");
INSERT INTO FileDB VALUES (2,"2.txt",49.08,NULL,0,"2.txt");
INSERT INTO FileDB VALUES (3,"3.txt",55.08,NULL,0,"3.txt");
INSERT INTO FileDB VALUES (4,"4.txt",65.08,NULL,0,"4.txt");
INSERT INTO FileDB VALUES (5,"5.txt",95.08,NULL,0,"5.txt");
