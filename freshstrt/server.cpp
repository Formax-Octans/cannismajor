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


// #include<sqlite3.h>

//conment after done with server.h
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

std::map<char *, ClientList *> map12;   //user node data


int server_sockfd = 0, client_sockfd = 0;
ClientList *root, *now;



void catch_ctrl_c_and_exit(int sig) {
    ClientList *tmp;
    while (root != NULL) {
        printf("\nClose socketfd: %d\n", root->data);
        close(root->data); // close all socket include server_sockfd
        tmp = root;
        root = root->link;
        free(tmp);
    }
    printf("Bye\n");
    exit(EXIT_SUCCESS);
}


void addMap(ClientNode *c)
{
  //check whtether user is correct
  // enter password


  string strint;
  std::cin >> strint;
  int n = strint.length();
  char name[n+1];
  strcpy(name, strint.c_str());
  // gets(name)

  if(map12.count(name)==1)
  {
    map12[name] = c;

  }
  else
  {
    perror("failed ");
    exit(0);
  }


}


void send_to_all_clients(ClientList *np, char tmp_buffer[])
{
    ClientList *tmp = root->link;
    while (tmp != NULL) {
        if (np->data != tmp->data) { // all clients except itself.
            printf("Send to sockfd %d: \"%s\" \n", tmp->data, tmp_buffer);
            send(tmp->data, tmp_buffer, LENGTH_SEND, 0);
        }
        tmp = tmp->link;
    }
}

void *client_handler(void *p_client)
{

  int leave_flag = 0;
  char nickname[LENGTH_NAME] = {};
  char recv_buffer[LENGTH_MSG] = {};
  char send_buffer[LENGTH_SEND] = {};
  ClientList *np = (ClientList *)p_client;

  if (recv(np->data, nickname, LENGTH_NAME, 0) <= 0 || strlen(nickname) < 2 || strlen(nickname) >= LENGTH_NAME-1) {
      printf("%s didn't input name.\n", np->ip);
      leave_flag = 1;
  } else {
      strncpy(np->name, nickname, LENGTH_NAME);
      printf("%s(%s)(%d) join the chatroom.\n", np->name, np->ip, np->data);
      sprintf(send_buffer, "%s(%s) join the chatroom.", np->name, np->ip);
      send_to_all_clients(np, send_buffer);
  }

  // while (1)
  // {
  //
  //     // if (leave_flag)
  //     // {
  //     //     break;
  //     // }
  //
  //
  // }
  //

  close(np->data);
free(np);

pthread_exit(0);


}






int main(int argc, char const *argv[])
{

  //handle signal
  signal(SIGINT, catch_ctrl_c_and_exit);

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
  server_info.sin_family = PF_INET;
  server_info.sin_addr.s_addr = INADDR_ANY;
  server_info.sin_port = htons(8888);


  bind(server_sockfd, (struct sockaddr *)&server_info, s_addrlen);
  listen(server_sockfd, 50);

  getsockname(server_sockfd, (struct sockaddr*) &server_info, (socklen_t*) &s_addrlen);

  printf("Start Server on: %s:%d\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));
// int x;
// std::cin >> x;
  // root = newNode(server_sockfd, inet_ntoa(server_info.sin_addr));
  // now = root;


  while (1)
  {
      client_sockfd = accept(server_sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);

      getpeername(client_sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);
      printf("Client user %s:%d come in.\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));
      printf("Reached here");

      ClientList *c = newNode(client_sockfd, inet_ntoa(client_info.sin_addr));
      // // ClientList *c = addMap(client_sockfd, inet_ntoa(client_info.sin_addr));
      // c->prev = now;
      // now->link = c;
      // now = c;
      addMap(c);
      pthread_t tid;
      // if (pthread_create(&tid,NULL,(void *)client_handler, (void *)c) != 0)
      if (pthread_create(&tid,NULL,client_handler, (void *)c) != 0)
      {
        perror("Create pthread error!\n");
        exit(EXIT_FAILURE);
      }

  }




  close(server_sockfd);
  return 0;
}
