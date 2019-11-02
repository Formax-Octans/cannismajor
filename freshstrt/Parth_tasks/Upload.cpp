#include <my_global.h>
#include <mysql.h>
#include <string>
#include <iostream>
using namespace std;

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

int main(int argc, char **argv)
{      
    MYSQL *con = mysql_init(NULL);
    
    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }  
    
    if (mysql_real_connect(con, "localhost", "user12", "34klq*", 
            "nimbus", 0, NULL, 0) == NULL) 
    {
        finish_with_error(con);
    }    

    string query="";
    string Filename, Fileptr;
    int Flag, uid, Size;
    int SIGN_IN_FLAG=1;
    //if user not signed IN. upload in public directory
    if(SIGN_IN_FLAG==0)
    {
        //upload filename.ext in table

        //extract data
        Filename = "BATMAN.mp4";   //passed as argument 
        Fileptr = "/home/parth/CN/BATMAN.mp4";
        

        Flag = SIGN_IN_FLAG;
        Size = 100;     //extract from original file

        uid =1;
        //extract uid using query in sign in function
        /*  in signin function. after validating and setting signin flag. 
            select username,password,uid from user user table where username = "thanos_6" and password = "123";
            from this extract uid;

        */



        query = "INSERT INTO FileDB(Filename,Fileptr,Flag,Size,uid) VALUES(\""+Filename+"\",\""+Fileptr+"\","+to_string(Flag)+"," + to_string(Size)+","+to_string(uid)+")";
        cout<<"\n Upload query: "<<query;
        if(mysql_query(con, query.c_str()));
        {
            finish_with_error(con);
        }
    }
    else
    {
         //upload filename.ext in table

        //extract data
        Filename = "SUPERMAN.mp4";   //passed as argument 
        Fileptr = "/home/parth/CN/SUPERMAN.mp4";
        

        Flag = SIGN_IN_FLAG;
        Size = 100;     //extract from original file
        uid =1;

        //extract uid using query in sign in function
        /*  in signin function. after validating and setting signin flag. 
            select username,password,uid from user user table where username = "thanos_6" and password = "123";
            from this extract uid;

        */


        query = "INSERT INTO FileDB(Filename,Fileptr,Flag,Size,uid) VALUES(\""+Filename+"\",\""+Fileptr+"\","+to_string(Flag)+"," + to_string(Size)+","+to_string(uid)+")";

        // query = "INSERT INTO FileDB(Filename,Fileptr,Flag,Size,uid) VALUES(\""+Filename+"\",\""+Fileptr+"\","+Flag+", "+Size+","+uid+")";
        cout<<"\n Upload query: "<<query;
        if(mysql_query(con, query.c_str()));
        {
            finish_with_error(con);

        }
    }
    
    cout<<"\n File uploaded succesfully: ";
    // mysql_free_result(result);
    mysql_close(con);
    
    
    exit(0);
}