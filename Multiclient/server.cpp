#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include<pthread.h>
using namespace std;

char msg[2000];
// char msg[1024];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void * socketThread(void *arg)
{
    cout << "Connected with client!" << endl;

  int newSocket = *((int *)arg);
  recv(newSocket , &msg , sizeof(msg) , 0);
  cout<<"from client: "<<msg;

  // Send message to the client socket 
  pthread_mutex_lock(&lock);
  char *message = (char*)malloc(sizeof(msg)+20);
  strcpy(message,"got msg : ");
  // strcat(message,msg);
  // strcat(message,"\n");
  strcpy(msg,message);
  free(message);
  pthread_mutex_unlock(&lock);
  sleep(1);
  //printf("%s",msg);
  send(newSocket,&msg,sizeof(msg),0);
  printf("Exit socketThread \n");
  close(newSocket);
  pthread_exit(NULL);
}
int main(){
  int serverSocket, newSocket;
  struct sockaddr_in serverAddr;    //servAddr
  bzero((char*)&serverAddr, sizeof(serverAddr));
//   struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  //Create the socket. 
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if(serverSocket < 0)
    {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }
  // Configure settings of the server address struct
  // Address family = Internet 
  serverAddr.sin_family = AF_INET;
  //Set port number, using htons function to use proper byte order 
  serverAddr.sin_port = htons(9009);
  //Set IP address to localhost 
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  //Set all bits of the padding field to 0 
  //memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  //Bind the address struct to the socket 
  int bindStatus = bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  if(bindStatus < 0)
    {
        cerr << "Error binding socket to local address" << endl;
        exit(0);
    }
    cout << "Waiting for a client to connect..." << endl;
  //Listen on the socket, with 40 max connection requests queued 
  if(listen(serverSocket,10)==0)
    printf("Listening\n");
  else
    printf("Error\n");

    pthread_t tid[10];
    int i = 0;
    while(1)
    {
        //Accept call creates a new socket for the incoming connection
        // addr_size = sizeof(serverStorage);
        // sockaddr_in newSockAddr;
        struct sockaddr_in newSockAddr;
        socklen_t newSockAddrSize = sizeof(newSockAddr);
        newSocket = accept(serverSocket, (struct sockaddr *) &newSockAddr, &newSockAddrSize);
        
        if(newSocket < 0)
    {
        cerr << "Error accepting request from client!" << endl;
        exit(1);
    }

        //for each client request creates a thread and assign the client request to it to process
       //so the main thread can entertain next request
        if( pthread_create(&tid[i], NULL, socketThread, &newSocket) != 0 )
           printf("Failed to create thread\n");
        if( i >= 10)
        {
          i = 0;
          while(i < 10)
          {
            pthread_join(tid[i++],NULL);
          }
          i = 0;
        }
    }
  return 0;
}