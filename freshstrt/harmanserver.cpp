//main server


#define MAXFILESIZE 512
#define MAXBUFFERSIEZ 512


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <iostream>
#include <map>
#include<vector>
#include <my_global.h>
#include <mysql.h>
#include "proto.h"
// #include "parser1.h"  //also function command parser
using namespace std;
int SIGN_IN_FLAG = 0 ;
int CURRENTUID = -1;
string CURRENT_USERNAME = "";



struct dataset
{
   string info1;
   string info2;
   string command_name;
   int status = 0;
};


typedef struct ClientNode {
    int data;
    struct ClientNode* prev;
    struct ClientNode* link;
    char ip[16];
    char name[31];
} ClientList;

ClientList *newNode(int sockfd, char* ip) {
    ClientList *np = (ClientList *)malloc( sizeof(ClientList) );
    np->data = sockfd;
    np->prev = NULL;
    np->link = NULL;
    strncpy(np->ip, ip, 16);
    strncpy(np->name, "NULL", 5);
    return np;
}
int server_sockfd = 0, client_sockfd = 0;

ClientList *root, *now;





void stringtochar(char arra[],string ar1)
{
  int length = ar1.length();
  std::cout << "Thats the wau i likeit" << '\n';
  for (int i = 0; i < length; i++)
  {
    arra[i] = ar1[i];
    printf("%c",arra[i]);

  }
  arra[length] = '\0';
}

string chartostring(char arra[],int n0)
{
  string str1="";
  int i;
  for ( i = 0; i!=n0; i++)
  {
    str1 += arra[i];
  }
str1 += '\0';
return str1;
}



void SHOW_BASE_DES()
{
  sleep(5);
  system("clear");
  std::cout << "----------------------------WELCOME TO DROPSHIT-----------------------" << '\n'<<endl<<endl;

}






















//commanding parsing










vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

dataset parser(string command)
{
//    string command;
    cout << "the commands is "<<command<<endl;
//    getline (cin, command);
    command+=" ";
    vector<string> words;
    words = split(command," ");
    int n = words.size();
    // std::cout << "  n"<<n << '\n';
    // for (int i = 0;i<n;i++)
    // {
    //     cout << words[i] << endl;
    // }
    // cout<<"1"<<endl;
    // datset initialisation
    dataset ds;
    //for account set up
    if(words[0].compare("account")==0)
    {

        ds.info1 = words[1];
        ds.info2 = words[2];
        ds.command_name = "account";
        ds.status = 1;
    }
    // else if(words[0].compare("sign_in")==0)
    // {
    //
    //     ds.info1 = words[1];
    //     ds.info2 = words[2];
    //     ds.command_name = "sign_in";
    //     ds.status = 1;
    // }
    else if(words[0].compare("upload")==0)
    {

        ds.info1 = words[1];
        ds.info2 = words[2];
        ds.command_name = "upload";
        ds.status = 1;
    }
    else if(words[0].compare("download")==0)
    {

        ds.info1 = words[1];
        ds.info2 = words[2];
        ds.command_name = "download";
        ds.status = 1;
    }
    else if(words[0].compare("sign_in")==0)
    {
        dataset cr;
        ds.info1 = words[1];
        ds.info2 = words[2];
        ds.command_name = "sign_in";
        ds.status = 1;
    }
    else if(words[0].compare("logout")==0)
    {
        dataset cr;
        ds.info1 = "null";
        ds.info2 = "null";
        ds.command_name = "logout";
        ds.status = 1;
    }
    else if(words[0].compare("view")==0)
    {
        dataset cr;
        ds.info1 = "null";
        ds.info2 = "null";
        ds.command_name = "view";
        ds.status = 1;
    }
    else if(words[0].compare("delete")==0)
    {
        dataset cr;
        ds.info1 = words[1];
        ds.info2 = "null";
        ds.command_name = "delete";
        ds.status = 1;
    }
    else{
        printf("ERROR: command not found\n");
    }
    return ds;
}




//mysql treatment









void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}




string initialview()
{
  // std::cout << "this is a  test" << '\n';
  // std::cin >> tam;

  string str1="";


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

  if (mysql_query(con, "SELECT Filename FROM FileDB where Flag = 0;"))
  {
      finish_with_error(con);
  }
  MYSQL_RES *result = mysql_store_result(con);

  if (result == NULL)
  {
      finish_with_error(con);

  }

  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;

  while ((row = mysql_fetch_row(result)))
  {
      for(int i = 0; i < num_fields; i++)
      {
          // printf("%s ", row[i] ? row[i] : "NULL");
          str1+= row[i] ? row[i] : "NULL";

      }
          // printf("\n");
          str1+="\n";
  }
   mysql_free_result(result);
  mysql_close(con);

  return str1;

}








string gotomyslbinder(dataset ds)
{

MYSQL *con = mysql_init(NULL);
string str1="";

if (con == NULL)
{
    fprintf(stderr, "mysql_init() failed\n");
    exit(1);
}
if (mysql_real_connect(con, "localhost", "user12", "34klq*", "nimbus", 0, NULL, 0) == NULL)
{
    finish_with_error(con);
}

    string c_name = ds.command_name;
    if(c_name.compare("upload")==0)
    {
        if(ds.status == 1)
        {
            /*
            enter the query here for upload
            */
        }

    }
    else if(c_name.compare("download")==0)
    {
        if(ds.status == 1)
        {
            /*
            enter the query here for download
            */
        }
    }
    else if(c_name.compare("account")==0)
    {
        if(ds.status == 1)
        {
            /*
            enter the query here for account
            */
        }
    }
    else if(c_name.compare("sign_in")==0)
    {
        if(ds.status == 1)
        {
            /*
            enter the query here for sign_in
            */

    string Username = ds.info1; //pass this string as arguments. comment this
    string Password = ds.info2; //pass this string as arguments

    cout<<"username received "<<Username<<"1"<<endl;
    cout<<"Password received "<<Password<<"1"<<endl;
    std::cout << Username.length() << '\n';
    std::cout << Password.length() << '\n';

    string query = "SELECT Username, Password FROM UserDB WHERE Username =\"" + Username + "\" AND Password = \""+Password+"\"" ;
            char queryinchar1[query.length()+1];
            cout<<"\nSql query:"<<query<<endl;
            Username = "Brosh_21";
            Password = "Birth12";
//            strncpy(queryinchar1,query.c_str(),query.length());
            // stringtochar(queryinchar1,query);
            // queryinchar1[query.length()] = '\0';

            // cout<<"\nSql query in character:"<<queryinchar1<<endl;
            // printf("\n Sql query in char %s",queryinchar1);

            if (mysql_query(con, query.c_str()))
            // if (mysql_query(con, queryinchar1))
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

            if(found==1)    //if found in table set signin flag = 1;
            {
                SIGN_IN_FLAG = 1;
//                cout<<"\n Logged in. ";
                str1 = "The username "+ Username +" has successfully logged in ";
                CURRENT_USERNAME = Username;
            }
            else
                str1 = "\n Incorrect Username or Password.\n ";
                cout<<"\n Incorrect Username or Password.\n ";





        }
    }
    else if(c_name.compare("delete")==0)
    {
        if(ds.status == 1)
        {
            /*
            enter the query here for delete
            */
        }
    }
    else if(c_name.compare("view")==0)
    {
      printf("Birchasgna\n" );

        if(ds.status == 1)
        {
          printf("Reached ehroihflksdng\n" );

          if (mysql_query(con, "SELECT Filename FROM FileDB where Flag = 0 ;"))
          {
              finish_with_error(con);
          }


          MYSQL_RES *result = mysql_store_result(con);

          if (result == NULL)
          {
              finish_with_error(con);

          }

          int num_fields = mysql_num_fields(result);

          MYSQL_ROW row;

          while ((row = mysql_fetch_row(result)))
          {
              for(int i = 0; i < num_fields; i++)
              {
                  // printf("%s ", row[i] ? row[i] : "NULL");
                  str1+= row[i] ? row[i] : "NULL";

              }
                  // printf("\n");
                  str1+="\n";
          }

          //harman update view manager

          // return str1;
          // printf("%s\n",str1 );
            // std::cout << str1 << '\n';

            // send case
            // int templenght = str1.length();
            // char array1[templenght+1] = {"lunda"};
            // strncpy(array1,str1.c_str(),templenght);
            // std::cout << "teja machuda later" << '\n';
            // std::cout << array1 << '\n';
            // send(localsocket,array1,MAXBUFFERSIEZ,0);

            // std::cout << "Selvarak" << '\n';


          //check status whethe signed it

          mysql_free_result(result);


        }
    }
    else
    {
        printf("NOT FOUND\n");
    }
     mysql_close(con);
     return str1; //return whatever the answer query is

}



























void *client_handler(void *p_client)
{
    // char menu[] = {"1. This is a sample text where all public files are supposed be here\n"};
    char menu[1000];

    // int menulenght = 1;

    int leave_flag = 0;
    int option_recv = -1;
    char nickname[LENGTH_NAME] = {};
    char recv_buffer[LENGTH_NAME] = {};
    char send_buffer[LENGTH_SEND] = {};
    char test12[] ={'a'};
    test12[0] = 12;
    ClientList *np = (ClientList *)p_client;
    string sendtofu,intialsenddata,sendatatoserver;
    char sendmainmessage[MAXBUFFERSIEZ];
    struct dataset parsedcommand;
    int i1 = 0,sendatatoserverlen=0;
    char c12 = 12;
    printf("\nReached here bruh\n" );
    intialsenddata = initialview();//tamper with menu
      strcpy(menu, intialsenddata.c_str());
      send(np->data,menu,sizeof(menu),0);
    while (1)
    {
        recv(np->data,recv_buffer,LENGTH_NAME,0);
        printf("Command recieved  %s\n", recv_buffer );
        if(recv_buffer[0]=='e' && recv_buffer[1]=='x' && recv_buffer[2]=='i' && recv_buffer[3]=='t' )
        {
          printf("Bye\n" );
          break;
        }


        sendtofu = chartostring(recv_buffer,strlen(recv_buffer));
        // std::cout << "Recieved buffer " <<sendtofu<< '\n';
        parsedcommand = parser(sendtofu);
        // std::cout << "1" <<parsedcommand.info1<< '\n';
        // std::cout << "2" <<parsedcommand.info2<< '\n';
        // std::cout << "3" <<parsedcommand.command_name<< '\n';
        // parsedcommand.command_name+=" ";
        sendatatoserver = gotomyslbinder(parsedcommand);//execute

        // @test begins
            strncpy(sendmainmessage,sendatatoserver.c_str(),sendatatoserver.length());
            // for ( int i = 0; i < sendatatoserver.length(); i++)//same as below for loop
        // for ( int i = 0; sendmainmessage[i]!='\0'; i++)
        // {
        //       printf("i= %d  sendmainmessage= %d sendmainmessage= %c  \n",i,sendmainmessage[i],sendmainmessage[i] );
        //
        // }
        if (parsedcommand.command_name=="view")
        {
          printf("\nChecked reaahces\n" );
          fflush(stdin);
          fflush(stdout);
        //
        //     // strncpy(sendmainmessage,sendatatoserver.c_str(),sendatatoserver.size());
            // strncpy(sendmainmessage,sendatatoserver.c_str(),sendatatoserver.length());
        //
        //     // sendmainmessage[0] = "h";sendmainmessage[1] = "o";
        //     // std::cin >> sendmainmessage;
        //     // std::cout << sendmainmessage << '\n';
        //     sendatatoserverlen = sendatatoserver.length();
        //     std::cout << "The length of sgring "<<sendatatoserverlen << '\n';
        //     send(np->data,&sendatatoserverlen,sizeof(int),0);
        //
        //     // write(np->data,test12,LENGTH_NAME);
        //
        //     while ((c12 = sendmainmessage[i1++])!='\0')
        //     {
        //       std::cout << "Tset"<<c12 << '\n';
        //       // send(np->data,&c12,sizeof(char),0);
        //       write(np->data,&c12,sizeof(char));
        //
        //
        //     }
        //     // write(np->data,)
        //     printf("again check\n" );
        //
        //

        // if(ifyoufail()==1){dont();}


        //clear buffer

        send(np->data,&c12,sizeof(char),0);
        send(np->data,sendmainmessage,MAXBUFFERSIEZ,0);
        // send(np->data,test12,sizeof(char*),0);
      }
      else if (parsedcommand.command_name=="view")
      {
        printf("\nChecked reaahces\n" );
        fflush(stdin);
        fflush(stdout);


      //clear buffer

      send(np->data,&c12,sizeof(char),0);
      send(np->data,sendmainmessage,MAXBUFFERSIEZ,0);
      // send(np->data,test12,sizeof(char*),0);
    }



    }




    pthread_exit(0);


}




int main(int argc, char const *argv[])
{


    server_sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (server_sockfd == -1)
    {
        printf("Faile\n" );
        exit(EXIT_FAILURE);

    }


    struct sockaddr_in server_info, client_info;
    int s_addrlen = sizeof(server_info);
    int c_addrlen = sizeof(client_info);
    memset(&server_info, 0, s_addrlen);
    memset(&client_info, 0, c_addrlen);
    server_info.sin_family = AF_INET;
    server_info.sin_addr.s_addr = INADDR_ANY;
    server_info.sin_port = htons(8888);



    bind(server_sockfd, (struct sockaddr *)&server_info, s_addrlen);
    listen(server_sockfd, 50);

    getsockname(server_sockfd, (struct sockaddr*) &server_info, (socklen_t*) &s_addrlen);

    printf("Start Server on: %s:%d\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));

    while (1)
    {
        client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_info,(socklen_t*)&c_addrlen);
        getpeername(client_sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);
        printf("Client user %s:%d come in.\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));
        printf("Reached here");
        ClientList *c = newNode(client_sockfd, inet_ntoa(client_info.sin_addr));
//        addMap(c);

        pthread_t tid;
        if (pthread_create(&tid,NULL,client_handler, c) != 0)
        {
            perror("Create pthread error!\n");
            exit(EXIT_FAILURE);
        }


    }
        printf("you are out");

    close(server_sockfd);
    return 0 ;

}
