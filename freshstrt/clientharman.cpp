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


int sockfd = 0;


char nickname[LENGTH_NAME] = {};







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
    if (err == -1) {
        printf("Connection to Server error!\n");
        exit(EXIT_FAILURE);
    }

    // Names
    getsockname(sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);
    getpeername(sockfd, (struct sockaddr*) &server_info, (socklen_t*) &s_addrlen);
    printf("Connect to Server: %s:%d\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));
    printf("You are: %s:%d\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

    char inoput[100];

    //recieving menu
    sleep(5);
    system("clear");
    std::cout << "----------------------------WELCOME TO DROPSHIT-----------------------" << '\n'<<endl<<endl;
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


    }

    close(sockfd);
    return 0;
}
