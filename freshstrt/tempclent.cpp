#define MAXBUFFERSIEZ 100
#define MAXFILESIZE 512

//only  for test purpose

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
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

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
//correct file name
static int getLine (char *prmpt, char *buff, size_t sz) {
    int ch, extra;

    // Get line with buffer overrun protection.
    if (prmpt != NULL) {
        printf ("%s", prmpt);
        fflush (stdout);
    }
    if (fgets (buff, sz, stdin) == NULL)
        return NO_INPUT;

    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    // Otherwise remove newline and give string back to caller.
    buff[strlen(buff)-1] = '\0';
    return OK;
}



int trimstringand_geextrension(trimsingdataype1 *inp)
{
  int filenamecount = 0,extensioncount = 0;
  int flag = 0;
    for (size_t i = 0; i < inp->lengthoforig; i++)
    {
      if (inp->orignalsing[i]=='.')
      {
        flag = 1;
        inp->buf[i] = '\0';
      }
        if (flag==0)
        {
          inp->buf[i] = inp->orignalsing[i];
          filenamecount++;
        }

      else if (flag==1)
      {

          inp->ext[i] = inp->orignalsing[i];
          extensioncount++;
      }

    }
    inp->ext[inp->lengthoforig] = '\0';

    return 1;
}






void catch_ctrl_c_and_exit(int sig) {
    flag = 1;
}

// void recv_msg_handler() {
//     char receiveMessage[LENGTH_SEND] = {};
//     while (1) {
//         int receive = recv(sockfd, receiveMessage, LENGTH_SEND, 0);
//         if (receive > 0) {
//             printf("\r%s\n", receiveMessage);
//             str_overwrite_stdout();
//         } else if (receive == 0) {
//             break;
//         } else {
//             // -1
//         }
//     }
// }

// void send_msg_handler() {
//     char message[LENGTH_MSG] = {};
//     while (1) {
//         str_overwrite_stdout();
//         while (fgets(message, LENGTH_MSG, stdin) != NULL) {
//             str_trim_lf(message, LENGTH_MSG);
//             if (strlen(message) == 0) {
//                 str_overwrite_stdout();
//             } else {
//                 break;
//             }
//         }
//         send(sockfd, message, LENGTH_MSG, 0);
//         if (strcmp(message, "exit") == 0) {
//             break;
//         }
//     }
//     catch_ctrl_c_and_exit(2);
// }
int main(int argc, char const *argv[])
// int main()
{
    signal(SIGINT, catch_ctrl_c_and_exit);
    char menu[MAXBUFFERSIEZ];

    // Naming
    printf("Please enter your name: ");
    if (fgets(nickname, LENGTH_NAME, stdin) != NULL) {
        str_trim_lf(nickname, LENGTH_NAME);
    }
    if (strlen(nickname) < 2 || strlen(nickname) >= LENGTH_NAME-1) {
        printf("\nName must be more than one and less than thirty characters.\n");
        exit(EXIT_FAILURE);
    }

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








    int length_menu = -1,menu_option = -1;
    char fielname[100],fieldata1[MAXFILESIZE];
    send(sockfd, nickname, LENGTH_NAME, 0);
    recv(sockfd, menu,MAXBUFFERSIEZ,0 );
    printf("\nThe menu :\n");
      printf("\nmenu =  %s",menu);
      printf("\n Enter option \n");
      scanf("%d",&menu_option );

      send(sockfd, &menu_option, sizeof(int), 0);
      FILE*fp;
      int c1;
      char c2;


      if (menu_option==1)
      {

        // going to send file
        printf("Enter the file name\n" ); //function required to separate the format
        // scanf("%s",filename );
        cin>>fielname;
//verify if dis shiz is ture
        printf("the text you entered %s",fielname);
        trimsingdataype1 filformat;
        filformat.lengthoforig = strlen(fielname);
        strncpy(filformat.orignalsing,fielname,MAXBUFFERSIEZ);

        trimstringand_geextrension(&filformat);
        printf("The file name is %s and file format is %s\n",filformat.buf , filformat.ext );
//do what ever with extension you want to


        // send(sockfd,fielname,MAXBUFFERSIEZ,0);
        write(sockfd,fielname,MAXBUFFERSIEZ);
        fp = fopen("add.txt", "r");

        // fp = fopen(filename, "r");
        while ((c1= fgetc(fp))!=EOF)
          {
            write(sockfd,&c1,sizeof(c1));
        //     send(sockfd,&c1,sizeof(c1),0);
        //
          }

          fclose(fp);


      }


      else if (menu_option == 2)
      {
          char filelist[MAXBUFFERSIEZ];
          printf("Select the file from list (number or name)\n" );
          recv(sockfd,filelist,sizeof(filelist),0);
          printf("\n%s",filelist );

      }




    // pthread_t send_msg_thread;
    // if (pthread_create(&send_msg_thread, NULL, (void *) send_msg_handler, NULL) != 0) {
    //     printf ("Create pthread error!\n");
    //     exit(EXIT_FAILURE);
    // }
    //
    // pthread_t recv_msg_thread;
    // if (pthread_create(&recv_msg_thread, NULL, (void *) recv_msg_handler, NULL) != 0) {
    //     printf ("Create pthread error!\n");
    //     exit(EXIT_FAILURE);
    // }

    // while (1) {
    //     if(flag) {
    //         printf("\nBye\n");
    //         break;
    //     }
    // }



    close(sockfd);
    return 0;
}
