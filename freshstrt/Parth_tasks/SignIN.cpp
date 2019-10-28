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

    string Username = "thanos_6"; //pass this string as arguments. comment this
    string Password = "123"; //pass this string as arguments

    
    string query = "SELECT Username, Password FROM UserDB WHERE Username =\"" + Username + "\" AND Password = \""+Password+"\"";
    //cout<<"\n query: "<<query;    checking if query is appended properly
    if (mysql_query(con, query.c_str())) 
    {
        finish_with_error(con);
    }
    
    MYSQL_RES *result = mysql_store_result(con);
    
    query="";
    if (result == NULL)   
    {
        finish_with_error(con);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    int found=0;    //0 means not in table
    
    while ((row = mysql_fetch_row(result))) 
    { 
        // cout<<"\n user: "<<row[0];       //printing table

        if((strcmp(row[0],Username.c_str())==0) && (strcmp(row[1],Password.c_str())==0))
        {
            found=1;
            break;
        }
    }

    int SIGN_IN_FLAG;
    if(found==1)    //if found in table set signin flag = 1;
    {
        SIGN_IN_FLAG = 1;
        cout<<"\n Logged in. ";
    
    }
    else
        cout<<"\n Incorrect Username or Password.\n ";
        
        

    
    //print to see if inserted or see in mysql
    
    if (mysql_query(con, "SELECT * FROM UserDB")) 
    {
        finish_with_error(con);
    }
    
    result = mysql_store_result(con);
    
    if (result == NULL) 
    {
        finish_with_error(con);
    }

    num_fields = mysql_num_fields(result);

    //   MYSQL_ROW row;
    
    while ((row = mysql_fetch_row(result))) 
    { 
        for(int i = 0; i < num_fields; i++) 
        { 
            printf("%s ", row[i] ? row[i] : "NULL"); 
        } 
            printf("\n"); 
    }
    
    mysql_free_result(result);
    mysql_close(con);
    
    
    exit(0);
}