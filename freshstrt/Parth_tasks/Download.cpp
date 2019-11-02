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
    
    if (mysql_real_connect(con, "localhost", "user12", "34klq*", "nimbus", 0, NULL, 0) == NULL) 
    {
        finish_with_error(con);
    }    

    string query="";
    string Filename, Fileptr;
    int Flag, uid, Size;
    int SIGN_IN_FLAG=1;
    
    //given command: download filename.ext
    Filename = "SUPERMAN.mp4";   //passed as argument 
    //extract the row with that filename
     query = "SELECT * FROM FileDB WHERE Filename = \""+ Filename+ "\"";
        cout<<"\n query: "<<query<<endl;

        if(mysql_query(con, query.c_str()))
        {
            finish_with_error(con);
        }
        // cout<<"\n query executed. ";

        MYSQL_RES *result = mysql_store_result(con);
    
    // query="";
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

        cout<<endl;
        cout<<" "<<row[0];
        cout<<" "<<row[1];
        cout<<" "<<row[2];
        cout<<" "<<row[3];
        cout<<" "<<row[4];
        cout<<" "<<row[5];


        

        if((strcmp(row[1],Filename.c_str())==0))
        {
            found=1;
            break;
        }
    }

    if(found==0)
    {
        cout<<"\n No such File. ";  //no file in database
    }
    else
    {
        //extract data from query;
        Flag = atoi(row[4]);
        Filename = row[1];
        Fileptr = row[5];
        uid = atoi(row[3]);
        Size = atoi(row[2]);

        if(Flag == 0)     //ie if flag == 0. file in public directory. allow hime to download
        {
            cout<<"\n public directory";
            cout<<"\n Allow download. ";
            //open file and tranfer file char by char
        }
        else
        {
            
            if(SIGN_IN_FLAG == 0)
            {
                cout<<"\n No such file. ";
            }
            else
            {
                //given UID of loggid user
                int givenuid = 1;
                if(uid == givenuid) 
                {
                    cout<<"\n Allow download. ";
                    //open file and tranfer file char by char
                }
                else
                {
                    cout<<"\n No such file. ";
                }
            }
        }
    }

    mysql_free_result(result);
    mysql_close(con);
 
    
    exit(0);
}