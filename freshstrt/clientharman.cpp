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
#include <fstream>

#include <vector>
#include <algorithm>
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

int SIGN_IN_FLAG = 0;
string CURRENT_USERNAME = "";


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
// str1 += '\0';
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
    // cout << "the commands is "<<command<<endl;
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
    //for sign_up set up
    if(words[0].compare("sign_up")==0)
    {

        ds.info1 = words[1];
        ds.info2 = words[2];
        ds.command_name = "sign_up";
        ds.status = 1;
    }
    else if(words[0].compare("clear")==0)
    {

        ds.info1 = "null";
        ds.info2 = "null";
        ds.command_name = "clear";
        ds.status = 1;
        // system("clear");
    }
    else if(words[0].compare("upload")==0)
    {

        ds.info1 = words[1];
        ds.info2 = words[2];
        ds.command_name = "upload";
        ds.status = 1;
        // std::cout << "I am not yaar " << '\n';
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






int send_throughsocket(char arr1[],int lenght,int sockfd1)
{
  // send(sockfd, inoput, sizecommand1*sizeof(char), 0);
  int i = 0;
  char c123;
  while (i<lenght)
  {
    c123 = arr1[i];
    send(sockfd1,&c123,sizeof(char),0);
    i++;

  }

return 0;

}



int recv_throughsocket(char arr1[],int lenght,int sockfd1)
{
  // send(sockfd, inoput, sizecommand1*sizeof(char), 0);
  int i = 0;
  char c123;
  while (i<lenght)
  {

    recv(sockfd1,&c123,sizeof(char),0);
    arr1[i] = c123;
    // std::cout << "Rceving "<<c123<<":" << '\n';

    i++;

  }
  arr1[i] = '\0';
  return 0;

}














void filter(vector<string> v)
{
    vector<string> images;
    vector<string> videos;
    vector<string> audios;
    vector<string> documents;
    vector<string> pdf;

    vector<string> others;
    vector<string> out;
    int n = v.size();
    for(int i = 0;i<n;i++)
    {
        out = split(v[i],".");
        if(out[1].compare("txt")==0)
        {
            documents.push_back(v[i]);
        }
        else if(out[1].compare("pdf")==0)
        {
            pdf.push_back(v[i]);
        }
        else if(out[1].compare("mp4")==0)
        {
            videos.push_back(v[i]);
        }
        else if(out[1].compare("mp3")==0)
        {
            audios.push_back(v[i]);
        }
        else if(out[1].compare("png")==0 || out[1].compare("jpeg")==0 || out[1].compare("jpg")==0 || out[1].compare("bmp")==0)
        {
            images.push_back(v[i]);
        }
        else
        {
            others.push_back(v[i]);
        }
    }
    //print in terminal
    int l = 6;
    int u = 10;
    cout<<"\033["<<l-5<<";1H\033[1;42m###################################################################################################################################\033[0m"<<endl;
    cout<<"\033["<<l-4<<";1H\033[1;42m#############                                                                                                           ###########\033[0m"<<endl;
    cout<<"\033["<<l-3<<";1H\033[1;42m#############                                                 NIMBUS                                                    ###########\033[0m"<<endl;
    cout<<"\033["<<l-2<<";1H\033[1;42m#############                                                                                                           ###########\033[0m"<<endl;
    cout<<"\033["<<l-1<<";1H\033[1;42m###################################################################################################################################\033[0m"<<endl;

    cout<<"\033["<<l+3<<";1HIMAGES"<<"\033["<<l+3<<";25HVIDEOS"<<"\033["<<l+3<<";50HDOCUMENTS"<<"\033["<<l+3<<";75HPDF"<<"\033["<<l+3<<";100HAUDIO"<<"\033["<<l+3<<";125HOTHER"<<endl;
    cout<<"\033["<<l+4<<";1H_______"<<"\033["<<u<<";25H________"<<"\033["<<u<<";50H_______________"<<"\033["<<u<<";75H______"<<"\033["<<u<<";100H_________"<<"\033["<<u<<";125H___________"<<endl;
    cout<<"\033["<<l+1<<";1HWelcome to public shared storage!:"<<endl;
    int isize= images.size();
    int vsize= videos.size();
    int dsize= documents.size();
    int psize= pdf.size();
    int asize= audios.size();
    int osize= others.size();

    vector<int> sizes{isize,vsize,dsize,psize,asize,osize};
    sort(sizes.begin(), sizes.end());
    int mx_lim = sizes[5];
    // for(int i = 0;i<sizes[0];i++)
    // {
    //     cout << images[i]<<"/t"<<videos[i] <<"/t"<<documents[i]<<"/t"<<pdf[i]<<"/t"<< audios[i]<<"/t"<<others[i]<< endl;

    // }
    int s = 11;
    int num = s;

        for(int i = 0;i<isize && i < 10;i++)
        {

            cout<<"\033["<<num+i<<";1H"<<images[i]<<endl;
        }
        num = s;
        for(int i = 0;i<vsize && i < 10;i++)
        {

            cout<<"\033["<<num+i<<";25H"<<videos[i]<<endl;
        }
        num = s;
        for(int i = 0;i<dsize && i < 10 ;i++)
        {

            cout<<"\033["<<num+i<<";50H"<<documents[i]<<endl;
        }
        num = s;
        for(int i = 0;i<psize && i < 10;i++)
        {

            cout<<"\033["<<num+i<<";75H"<<pdf[i]<<endl;
        }
        num = s;
        for(int i = 0;i<asize && i < 10;i++)
        {

            cout<<"\033["<<num+i<<";100H"<<audios[i]<<endl;
        }
        num = s;
        for(int i = 0;i<osize && i < 10;i++)
        {

            cout<<"\033["<<num+i<<";125H"<<others[i]<<endl;
        }
    int b = 22;
    cout<<"\033["<<b  <<";1H\033[1;32m>>$To create a private ACCOUNT use : 'account username password'\033[0m"<<endl;
    cout<<"\033["<<b+1<<";1H\033[1;32m>>$To UPLOAD use                   : 'upload filename extension'\033[0m"<<endl;
    cout<<"\033["<<b+2<<";1H\033[1;32m>>$To DOWNLOAD use                 : 'download filename extension'\033[0m"<<endl;
    cout<<"\033["<<b+3<<";1H\033[1;32m>>$To SIGN IN use                  : 'sign_in username password'\033[0m"<<endl;
    cout<<"\033["<<b+4<<";1H\033[1;32m>>$To view use                     : 'view'\033[0m"<<endl;
    cout<<"\033["<<b+4<<";1H\033[1;32m>>$To delete use                   : 'delete filename .extension'\033[0m"<<endl;

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

    char inoput[MAXBUFFERSIEZ];
    string inoputstring;
    struct dataset parsedcommand;
    char recievemainmessage[MAXBUFFERSIEZ];
    int c1;
    string recievemainmessagestr="";
    int recievemainmessagestrlength= 0;
    int flagtemp=0,sizecommand1;
    int receivemenulength1;
    int usernamelenth;
    int found11 = -1;
    string fielname= "";
    string fielname2= "";

    //recieving menu
    SHOW_BASE_DES();//basic design
    // std::cout << "----------------------------WELCOME TO DROPSHIT-----------------------" << '\n'<<endl<<endl;
    recv(sockfd,&receivemenulength1,sizeof(int),0 );
    // recv(sockfd,menu,sizeof(char)*receivemenulength1,0 );
    // std::cout << "menu leght"<<receivemenulength1 << '\n';
    recv_throughsocket(menu,receivemenulength1,sockfd);
    std::vector<string> v1 = split(menu,"\n");
    filter(v1);
    // printf("\n%s\n",menu);

    while (1)
    {
          printf(">> " );
          // cin.flush();
          cin.getline(inoput,MAXBUFFERSIEZ);
          // send(sockfd, inoput, sizeof(inoput), 0);
          sizecommand1 = strlen(inoput);
          if (sizecommand1<4)
          {
            system("clear");
            printf("\n" );
            continue;
          }
          send(sockfd, &sizecommand1, sizeof(int), 0);

          // send(sockfd, inoput, sizecommand1*sizeof(char), 0);
          send_throughsocket(inoput,sizecommand1,sockfd);

          if(inoput[0]=='e' && inoput[1]=='x' && inoput[2]=='i' && inoput[3]=='t' )
          {
            printf("Bye\n" );
            break;

          }

          inoputstring = chartostring(inoput,strlen(inoput));
          parsedcommand = parserprinter(inoputstring,sockfd);
          // std::cout << "INput string" << '\n';
          // std::cout << inoputstring << '\n';
          // std::cout << "parsedcommand" << '\n';
          // std::cout << parsedcommand.info1 << '\n';
          // std::cout << parsedcommand.command_name << '\n';
          // std::cout << parsedcommand.info2 << '\n';
          // std::cout << parsedcommand.status << '\n';
          if (parsedcommand.command_name=="view")
          {
            fflush(stdin);
            fflush(stdout);
            // std::cout << "Utpatang" << '\n';
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
              // while (recv(sockfd,&c1,sizeof(char),0))
              // {
              //
              //     if (c1==12)
              //     {
              //       break;
              //     }
              //
              // }
              // recv(sockfd,&recievemainmessage,sizeof(recievemainmessage),0);

              // }
              recv(sockfd,&recievemainmessagestrlength,sizeof(int),0);
              // recv(sockfd,recievemainmessage,recievemainmessagestrlength*sizeof(char),0);
              recv_throughsocket(recievemainmessage,recievemainmessagestrlength,sockfd);


              // std::cout << recievemainmessage << '\n';
              v1 = split(chartostring(recievemainmessage,recievemainmessagestrlength),"\n");
              filter(v1);
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
            // fflush(stdin);
            // fflush(stdout);
            // std::cout << "Utpatang" << '\n';
              // while (recv(sockfd,&c1,sizeof(char),0))
              // {
              //
              //     if (c1==14)
              //     {
              //       break;
              //     }
              //


              // }

              recv(sockfd,&SIGN_IN_FLAG,sizeof(int),0);
              recv(sockfd,&usernamelenth,sizeof(int),0);
              char tempstring12[usernamelenth+1];
              recv_throughsocket(tempstring12,usernamelenth,sockfd);
              // strcpy(CURRENT_USERNAME,tempstring12.c_str());
              CURRENT_USERNAME = chartostring(tempstring12,usernamelenth);


              recv(sockfd,&recievemainmessagestrlength,sizeof(int),0);
              // recv(sockfd,recievemainmessage,recievemainmessagestrlength*sizeof(char),0);
              recv_throughsocket(recievemainmessage,recievemainmessagestrlength,sockfd);


              std::cout << "\n\nSign in message" << '\n';
              std::cout << "the message length received " << recievemainmessagestrlength<<'\n';
              std::cout << recievemainmessage << '\n';
              std::cout << "SIGN IN status " << SIGN_IN_FLAG<<'\n';
              std::cout << "CUURENT USSERNIGGA " <<CURRENT_USERNAME<< '\n';

          //
          }
          else if (parsedcommand.command_name=="sign_up")
          {
            // fflush(stdin);

              // }
              recv(sockfd,&recievemainmessagestrlength,sizeof(int),0);
              // recv(sockfd,recievemainmessage,recievemainmessagestrlength*sizeof(char),0);
              recv_throughsocket(recievemainmessage,recievemainmessagestrlength,sockfd);


              std::cout << "\n\nSign up message" << '\n';
              std::cout << "the message length received " << recievemainmessagestrlength<<'\n';
              std::cout << recievemainmessage << '\n';

          //
          }
          else if (parsedcommand.command_name=="logout")
          {

            recv(sockfd,&SIGN_IN_FLAG,sizeof(int),0);

              recv(sockfd,&recievemainmessagestrlength,sizeof(int),0);
              // recv(sockfd,recievemainmessage,recievemainmessagestrlength*sizeof(char),0);
              recv_throughsocket(recievemainmessage,recievemainmessagestrlength,sockfd);


              std::cout << "the message length received " << recievemainmessagestrlength<<'\n';
              std::cout << recievemainmessage << '\n';
          }
          else if (parsedcommand.command_name=="delete")
          {
              recv(sockfd,&recievemainmessagestrlength,sizeof(int),0);
              // recv(sockfd,recievemainmessage,recievemainmessagestrlength*sizeof(char),0);
              recv_throughsocket(recievemainmessage,recievemainmessagestrlength,sockfd);


              // std::cout << "the message length received " << recievemainmessagestrlength<<'\n';
              std::cout << recievemainmessage << '\n';
          }
          else if (parsedcommand.command_name=="upload")
          {
            int tempo;//for checking whether the file exist
            std::cout << "Reached upload" << '\n';
            recv(sockfd,&found11,sizeof(int),0);
            std::cout << found11 << '\n';
            // cin.getline(fielname,MAXBUFFERSIEZ);
            // char c[10240];
            if(found11 == 1)
            {
              std::cout << "File name already exists try again" << '\n';
            }
            else
            {
              std::cout << "\nENTER THE PATH OF FILE" << '\n';
              std::cin >> fielname;
              // std::cin >> fielname2;

              // scanf("%s",fielname);
              // fielname+=".txt";
              // fielname = fielname+"."+fielname2;
              std::cout << fielname << '\n';
              char fielnae1[fielname.length()+1] ;
              strcpy(fielnae1,fielname.c_str());


              fstream f1;
              char ch23;
              int bytesRead, bytesWritten = 0;

              f1.open(fielnae1, ios::in | ios::binary);
              tempo = f1.fail();
              send(sockfd,&tempo,sizeof(int),0);

              if (tempo)
              {
                        std::cout << "No such file" << '\n';
              }

              else
              {

                  while(!f1.eof())
                  {

                   ch23 = f1.get();

                   bytesWritten +=send(sockfd, &ch23, sizeof(ch23),0); //strlen(ch23)

                 }
                 ch23 = 3;
                 send(sockfd, &ch23, sizeof(ch23),0); //strlen(ch23)
                  cout<<"\n File sended successfully. \n";

              }


              f1.close();

              sleep(3);



            //   FILE *fp1;
            // fp1 = fopen(fielnae1,"r");
            // string sendfielthrougvar="";
            // int seizofsendfielthroughvar = 0;
          	// while ((c1= fgetc(fp1))!=EOF)
        	  //    {
      			// 		// write(sockfd,&c1,sizeof(int));
            //     // std::cout << "check" << '\n';
            //     // std::cout << c1 << '\n';
            //     // printf("%c\n",c1);
            //     sendfielthrougvar +=c1;
          	//    }
            //   fclose(fp1);
          	//     seizofsendfielthroughvar = sendfielthrougvar.length();
            //     char sendfielthrougvarchar[seizofsendfielthroughvar+1];
            //   send(sockfd,&seizofsendfielthroughvar,sizeof(int),0);
            //   strcpy(sendfielthrougvarchar,sendfielthrougvar.c_str());
            //   send_throughsocket(sendfielthrougvarchar,seizofsendfielthroughvar,sockfd);
            //




            }





          }

          else if (parsedcommand.command_name=="clear")
          {
            system("clear");
          }



    }

    close(sockfd);
    return 0;
}
