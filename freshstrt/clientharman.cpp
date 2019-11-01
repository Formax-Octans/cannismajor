#define MAXBUFFERSIEZ 100
#define MAXFILESIZE 512

//only  for test purpose

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <netdb.h>
#include "proto.h"
#include "string.h"
#include <iostream>
#include <vector>
// Global variables
using namespace std;
volatile sig_atomic_t flag = 0;/////fuck

typedef struct trimsingdataype
{
  char *orignalsing;
  int lengthoforig;
  char *buf;//filename
  int buflength;
  char *ext;//extension
  int extlengthl;
}trimsingdataype1;

struct dataset
{
   string info1;
   string info2;
   string command_name;
   int status = 0;
};
int sockfd = 0;


char nickname[LENGTH_NAME] = {};




void SHOW_BASE_DES()
{
  sleep(5);
  system("clear");
  std::cout << "----------------------------WELCOME TO DROPSHIT-----------------------" << '\n'<<endl<<endl;

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

dataset parserprinter(string command,int locaksocket1)
{
//    string command;
    char printout[MAXBUFFERSIEZ];
    string printoutsgtr;
    cout << "the commands is "<<command<<endl;
//    getline (cin, command);
    // command+=" ";
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
        std::cout << "\nVIEW \n\n\n" << '\n';


        // recv(locaksocket1, printout, MAXBUFFERSIEZ, 0);
        // std::cout << printout << '\n';
        // printoutsgtr = chartostring(printout,strlen(printout));
        // std::cout << printoutsgtr << '\n';

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























void catch_ctrl_c_and_exit(int sig) {
    flag = 1;
}


int main(int argc, char const *argv[])
// int main()
{
    signal(SIGINT, catch_ctrl_c_and_exit);
    char menu[MAXBUFFERSIEZ];

    // Naming
    // printf("Please enter your name: ");
    // if (fgets(nickname, LENGTH_NAME, stdin) != NULL) {
    //     str_trim_lf(nickname, LENGTH_NAME);
    // }
    // if (strlen(nickname) < 2 || strlen(nickname) >= LENGTH_NAME-1) {
    //     printf("\nName must be more than one and less than thirty characters.\n");
    //     exit(EXIT_FAILURE);
    // }

    // Create socket
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (sockfd == -1) {
        printf("Fail to create a socket.");
        exit(EXIT_FAILURE);
    }

    // Socket information
    struct sockaddr_in server_info, client_info;
    struct hostent *server;
    int s_addrlen = sizeof(server_info);
    int c_addrlen = sizeof(client_info);
    memset(&server_info, 0, s_addrlen);
    memset(&client_info, 0, c_addrlen);
    bzero((char *) &server_info, sizeof(server_info));
    // server_info.sin_family = PF_INET;
    server_info.sin_family = AF_INET;
    // server_info.sin_addr.s_addr = inet_addr("127.0.0.1");

    server = gethostbyname(argv[1]);
    // server_info.sin_addr.s_addr = inet_addr("127.0.0.1");
    bcopy((char *)server->h_addr,  (char *)&server_info.sin_addr.s_addr,  server->h_length);
    server_info.sin_port = htons(8888);
    // server_info.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to Server
    int err = connect(sockfd, (struct sockaddr *)&server_info, s_addrlen);
    if (err == -1)
    {
        printf("Connection to Server error!\n");
        exit(EXIT_FAILURE);
    }

    // Names
    getsockname(sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);
    getpeername(sockfd, (struct sockaddr*) &server_info, (socklen_t*) &s_addrlen);
    printf("Connect to Server: %s:%d\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));
    printf("You are: %s:%d\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

    char inoput[LENGTH_NAME];
    string inoputstring;
    struct dataset parsedcommand;
    char recievemainmessage[MAXBUFFERSIEZ];
    char c1;
    string recievemainmessagestr="";
    int recievemainmessagestrlength= 0;
    int flagtemp=0;

    //recieving menu
    SHOW_BASE_DES();//basic design
    // std::cout << "----------------------------WELCOME TO DROPSHIT-----------------------" << '\n'<<endl<<endl;
    recv(sockfd, menu,MAXBUFFERSIEZ,0 );
    printf("\n%s\n",menu);

    while (1)
    {
          printf(">> " );
          cin.getline(inoput,MAXBUFFERSIEZ);
          send(sockfd, inoput, LENGTH_NAME, 0);
          if(inoput[0]=='e' && inoput[1]=='x' && inoput[2]=='i' && inoput[3]=='t' )
          {
            printf("Bye\n" );
            break;

          }
          inoputstring = chartostring(inoput,strlen(inoput));
          parsedcommand = parserprinter(inoputstring,sockfd);
          if (parsedcommand.command_name=="view")
          {
            fflush(stdin);
            fflush(stdout);
            std::cout << "Utpatang" << '\n';
          //   bzero((char*)&recievemainmessage,sizeof(recievemainmessage));
              // while(recv(sockfd,recievemainmessage,MAXBUFFERSIEZ,0))
              // {
              //   int jk;
              //   for ( jk = 0; recievemainmessage[jk]!=12 && jk<strlen(recievemainmessage); jk++)
              //   {
              //     printf("jk= %d  recievemainmessage= %d recievemainmessage= %c  \n",jk,recievemainmessage[jk],recievemainmessage[jk] );
              //
              //   }
              //   if (recievemainmessage[jk]==12)
              //   {
              //     break;
              //   }
              // }
              while (recv(sockfd,&c1,sizeof(char),0))
              {

                  if (c1==12)
                  {
                    break;
                  }

              }
              recv(sockfd,recievemainmessage,MAXBUFFERSIEZ,0);

              std::cout << "\n\nVIEWbirth" << '\n';
              std::cout << recievemainmessage << '\n';
              // for (int i = 0; recievemainmessage[i]!='\0'; i++)
              // {
              //
              //   printf("i= %d  recievemainmessage= %d recievemainmessage= %c  \n",i,recievemainmessage[i],recievemainmessage[i] );
              //
              //
              // }
            // recievemainmessagestr = chartostring(recievemainmessage,strlen(recievemainmessage));
            //
            // std::cout << "\nString format of answer" << '\n';
            // std::cout << recievemainmessagestr << '\n';

          //     // read(sockfd,recievemainmessage,LENGTH_NAME);
          //     // read(sockfd,recievemainmessage,LENGTH_NAME);
          //     // read(sockfd,&reDmzfc,sizeof(int));
          //     // read(sockfd,recievemainmessage,LENGTH_NAME);
          //
          //     recv(sockfd,&recievemainmessagestrlength,sizeof(int),0);
          //     std::cout << "\nRecieved string lenght"<<recievemainmessagestrlength << '\n';
          //     // while (recv(sockfd,&c1,sizeof(char),0))
          //     while (read(sockfd,&c1,sizeof(char)))
          //     {
          //       std::cout << "c1"<<c1 << '\n';
          //       recievemainmessagestr+=c1;
          //       flagtemp++;
          //       if (flagtemp == recievemainmessagestrlength)
          //       {
          //
          //           break;
          //       }
          //       std::cout <<"\nflagtemp " <<flagtemp << '\n';
          //     }
          //
          //

          //
          }

          else if (parsedcommand.command_name=="sign_in")
          {
            fflush(stdin);
            fflush(stdout);
            // std::cout << "Utpatang" << '\n';
              while (recv(sockfd,&c1,sizeof(char),0))
              {

                  if (c1==12)
                  {
                    break;
                  }

              }
              // recv(sockfd,recievemainmessage,MAXBUFFERSIEZ,0);

              std::cout << "\n\nVIEWbirth" << '\n';
              std::cout << recievemainmessage << '\n';

          //
          }



    }

    close(sockfd);
    return 0;
}
