# cannismajor



  1 open cannismajor
  2 open freshstrt
  3 g++ clientharman.cpp -o clent string.o
  4 
  5 g++ harmanserver.cpp -o sever -lpthread  `mysql_config --cflags --libs`
  6 
  7 compile ./sever
  8 
  9 compile ./clent localhost
 10 
 11 FEATURES:
 12 ONLY FOR LINUX ENVIRONMENT+
 13 multiclient allowed :32000 threads limited
 14 signal handler present for handling segmentation fault (in some cases)
 15 independent database present(requires mysql client)
 16 sign_up username password : adds username and passwords in database
 17 clear : clear the console
 18 upload filename extension   : enter the path or the name of file along with extension 
 19 download filename extension   : the file will download to current path
 20 logout : logout if signed in
 21 view : gives keyborad arrow movement
 22 


