/*
  source: DZONE.com 
  
  compiling using
  g++ client.cpp -lpthread -o client

  ./client

*/

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
void * cientThread(void *arg)
{
  printf("In thread\n");
  char msg[1000];
//   char msg[1024];
  int clientSocket;
  struct sockaddr_in serverAddr;    //sendSockAddr
  bzero((char*)&serverAddr, sizeof(serverAddr));
  socklen_t addr_size;
  // Create the socket. 
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  //Configure settings of the server address
 // Address family is Internet 
  serverAddr.sin_family = AF_INET;
  //Set port number, using htons function 
  serverAddr.sin_port = htons(9009);
 //Set IP address to localhost
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  // memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    //Connect the socket to the server using the address
    addr_size = sizeof(serverAddr);
    int status = connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    if(status < 0)
    {
        cout<<"Error connecting to socket!"<<endl; 
		exit(0);
    }

    cout << "Connected to the server!" << endl;

    memset(&msg, 0, sizeof(msg));
    strcpy(msg,"Hello");
   if( send(clientSocket ,&msg , sizeof(msg) , 0) < 0)
    {
            printf("Send failed\n");
    }
    //Read the msg from the server into the msg
    memset(&msg, 0, sizeof(msg));
    if(recv(clientSocket, &msg, sizeof(msg), 0) < 0)
    {
       printf("Receive failed\n");
    }
    //Print the received msg
    //printf("Data received: %s\n",msg);
    cout<<"\n Data received: "<<msg;
    close(clientSocket);
    pthread_exit(NULL);
}
int main(){
  int i = 0;
  pthread_t tid;
//   while(i< 50)
//   {
    if( pthread_create(&tid, NULL, cientThread, NULL) != 0 )
           printf("Failed to create thread\n");
//     i++;
//   }
  //sleep(20);
//   i = 0;
//   while(i< 50)
//   {
     pthread_join(tid,NULL);
     printf("%d:\n",i);
//   }
  return 0;
}