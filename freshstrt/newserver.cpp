#define MAXFILESIZE 512
#define MAXBUFFERSIEZ 512


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
#include <iostream>
#include <map>
#include "proto.h"
using namespace std;



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


void *client_handler(void *p_client)
{
    char menu[] = {"1. Enter 1 for sending file \n 2. Enter 2 for reciveong file chose from collection"};
    // int menulenght = 1;

    int leave_flag = 0;
    int option_recv = -1;
    char nickname[LENGTH_NAME] = {};
    char recv_buffer[LENGTH_MSG] = {};
    char send_buffer[LENGTH_SEND] = {};
    ClientList *np = (ClientList *)p_client;

    if (recv(np->data, nickname, LENGTH_NAME, 0) <= 0 || strlen(nickname) < 2 || strlen(nickname) >= LENGTH_NAME-1) {
        printf("%s didn't input name.\n", np->ip);
        leave_flag = 1;
    } else {
        strncpy(np->name, nickname, LENGTH_NAME);
        printf("%s(%s)(%d) join the server.\n", np->name, np->ip, np->data);
        sprintf(send_buffer, "%s(%s) join the server.", np->name, np->ip);
        // send_to_all_clients(np, send_buffer);
    }
//send menu
    send(np->data,menu,sizeof(menu),0);
    // send(np->data,&menulenght,sizeof(int),0);
    recv(np->data,&option_recv,sizeof(int),0);
    FILE *fp;
    int lenght1;
    char filename[100];
    int c1;
    char buf12[MAXFILESIZE];
    if (option_recv==1)
    {
      printf("\nOption recieved is 1\n" );

      // recv(np->data, filename, MAXBUFFERSIEZ,0);
      read(np->data, filename, sizeof(filename));
      printf("\nRecieve filename %s \n",filename );
      // fp = fopen("add.txt","w"); //just for testing purpose
      fp = fopen(filename,"w"); //just for testing purpose

      while (read(np->data,&c1,sizeof(c1)))
      // while (recv(np->data, &c1, sizeof(c1),0))
      {
        // fwrite(c,sizeof(c),1,fp2);
          fputc(c1,fp);
          // printf("%c",c1 );
      }


      fclose(fp);
    }

    else if (option_recv == 2)
    {
      /* code */
      // char *filelist = getfile_name();
      char filelist[] = {"1 1.txt\n 2. 2.txt \n3 3.txt"};
      send(np->data, filelist,sizeof(filelist),0);

    }


    close(np->data);
    free(np);
    std::cout << "\nFREED" << '\n';
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
