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

    vector<string> words;
    words = split(command," ");
    int n = words.size();
    // for (int i = 0;i<n;i++)
    // {
    //     cout << words[i] << endl;
    // }
    //datset initialisation
    dataset ds;
    //for account set up
    if(words[0].compare("account")==0)
    {

        ds.info1 = words[1];
        ds.info2 = words[2];
        ds.command_name = "account";
        ds.status = 1;
    }
    else if(words[0].compare("sign_in")==0)
    {

        ds.info1 = words[1];
        ds.info2 = words[2];
        ds.command_name = "sign_in";
        ds.status = 1;
    }
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

  return str1;

}








void gotomyslbinder(dataset ds)
{
    string c_name = ds.command_name;
    if(c_name.compare("upload"))
    {
        if(ds.status == 1)
        {
            /*
            enter the query here for upload
            */
        }

    }
    else if(c_name.compare("download"))
    {
        if(ds.status == 1)
        {
            /*
            enter the query here for download
            */
        }
    }
    else if(c_name.compare("account"))
    {
        if(ds.status == 1)
        {
            /*
            enter the query here for account
            */
        }
    }
    else if(c_name.compare("sign_in"))
    {
        if(ds.status == 1)
        {
            /*
            enter the query here for sign_in
            */
        }
    }
    else if(c_name.compare("delete"))
    {
        if(ds.status == 1)
        {
            /*
            enter the query here for delete
            */
        }
    }
    else if(c_name.compare("view"))
    {
        if(ds.status == 1)
        {
            
        }
    }
    else
    {
        printf("NOT FOUND\n");
    }

}



























void *client_handler(void *p_client)
{
    // char menu[] = {"1. This is a sample text where all public files are supposed be here\n"};
    char menu[1000];

    // int menulenght = 1;

    int leave_flag = 0;
    int option_recv = -1;
    char nickname[LENGTH_NAME] = {};
    char recv_buffer[LENGTH_MSG] = {};
    char send_buffer[LENGTH_SEND] = {};
    ClientList *np = (ClientList *)p_client;
    string sendtofu,intialsenddata;
    struct dataset parsedcommand;
    printf("\nReached here bruh\n" );
    intialsenddata = initialview();//tampler with menu
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
        gotomyslbinder(parsedcommand);
        // if(ifyoufail()==1){dont();}

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
