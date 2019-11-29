#define MAXBUFFERSIEZ 100
#define MAXFILESIZE 512


#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4
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
#include <sstream>
#include <curses.h>

#include <menu.h>


char dfile[200];

const char *choices[] = {
                        "Choice 1", "Choice 2", "Choice 3", "Choice 4", "Choice 5",
			"Choice 6", "Choice 7", "Choice 8", "Choice 9", "Choice 10",
			"Choice 11", "Choice 12", "Choice 13", "Choice 14", "Choice 15",
			"Choice 16", "Choice 17", "Choice 18", "Choice 19", "Choice 20",
                        "Exit",
                        NULL
                  };
const std::string red("\033[0;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string cyan("\033[0;36m");
const std::string magenta("\033[0;35m");
const std::string reset("\033[0m");








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
float MEMORY_LET = -1;
string download_path = "/home/i7-workstation/Desktop/mainpro/cannismajor/freshstrt/clientfiels/";


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



vector<string> split1(string str)
{
	// Used to split string around spaces.
	istringstream ss(str);
    vector<string> l;
	// Traverse through all words
	do {
		// Read a word
		string word;
		ss >> word;

		// Print the read word
		cout << word << endl;
    l.push_back(word);


		// While there is more to read
	} while (ss);

    return l;
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



void filter1(vector<string> v,vector<string> priv,string usr,int left_str)
{
  system("clear");

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

    cout<<"\033["<<l+5<<";1HIMAGES"<<"\033["<<l+5<<";20HVIDEOS"<<"\033["<<l+5<<";40HDOCUMENTS"<<"\033["<<l+5<<";60HPDF"<<"\033["<<l+5<<";80HAUDIO"<<"\033["<<l+5<<";100HOTHER"<<"\033["<<l+5<<";120H|"<<"\033["<<l+5<<";125HPRIVATE"<<endl;

    cout<<"\033["<<l+6<<";1H________________________________________________________________________________________________________________________________________"<<endl;

    //cout<<"\033["<<l+6<<";1H_______"<<"\033["<<l+6<<";15H________"<<"\033["<<l+6<<";25H_________"<<"\033["<<l+6<<";35H______"<<"\033["<<l+6<<";45H_______"<<"\033["<<l+6<<";55H_________"<<endl;
    cout<<"\033["<<l+1<<";1HWelcome to your private storage!:"<<endl;
    cout<<"\033["<<l+2<<";HUsername : "<<usr<< endl;
    cout<<"\033["<<l+3<<";1HSTORAGE LEFT:"<<left_str<<endl;
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
    int s = 15;
    int num = s;

        for(int i = 0;i<isize && i < 10;i++)
        {

            cout<<"\033["<<num+i<<";1H"<<images[i]<<endl;
        }
        num = s;
        for(int i = 0;i<vsize && i < 10;i++)
        {

            cout<<"\033["<<num+i<<";20H"<<videos[i]<<endl;
        }
        num = s;
        for(int i = 0;i<dsize && i < 10 ;i++)
        {

            cout<<"\033["<<num+i<<";40H"<<documents[i]<<endl;
        }
        num = s;
        for(int i = 0;i<psize && i < 10;i++)
        {

            cout<<"\033["<<num+i<<";60H"<<pdf[i]<<endl;
        }
        num = s;
        for(int i = 0;i<asize && i < 10;i++)
        {

            cout<<"\033["<<num+i<<";80H"<<audios[i]<<endl;
        }
        num = s;
        for(int i = 0;i<osize && i < 10;i++)
        {

            cout<<"\033["<<num+i<<";100H"<<others[i]<<endl;
        }
        for(int i = 0;i < 10;i++)
        {

            cout<<"\033["<<num+i<<";120H"<<"|"<<endl;
        }
        for(int i = 0;i < priv.size() && i < 10;i++)
        {

            cout<<"\033["<<num+i<<";125H"<<priv[i]<<endl;
        }
    int b = 30;
    // cout<<"\033["<<b  <<";1H\033[1;32m>>$To create a private ACCOUNT use : 'account username password'\033[0m"<<endl;
    // cout<<"\033["<<b+1<<";1H\033[1;32m>>$To UPLOAD use                   : 'upload filename .extension'\033[0m"<<endl;
    // cout<<"\033["<<b+2<<";1H\033[1;32m>>$To DOWNLOAD use                 : 'download filename .extension'\033[0m"<<endl;
    // cout<<"\033["<<b+3<<";1H\033[1;32m>>$To SIGN IN use                  : 'sign_in username password'\033[0m"<<endl;
    // cout<<"\033["<<b+4<<";1H\033[1;32m>>$To view use                     : 'view'\033[0m"<<endl;
    // cout<<"\033["<<b+4<<";1H\033[1;32m>>$To delete use                   : 'delete filename .extension'\033[0m"<<endl;
    cout<<"\033["<<b  <<";1H\033[1;32m"<<yellow<<">>$ "<<green<<" To create a private ACCOUNT use :"<<cyan<< "  'account username password'\033[0m"<<endl;
    cout<<"\033["<<b+1<<";1H\033[1;32m"<<yellow<<">>$ "<<green<<" To UPLOAD use                   :"<<cyan<< "  'upload filename extension'\033[0m"<<endl;
    cout<<"\033["<<b+2<<";1H\033[1;32m"<<yellow<<">>$ "<<green<<" To DOWNLOAD use                 :"<<cyan<< "  'download filename extension'\033[0m"<<endl;
    cout<<"\033["<<b+3<<";1H\033[1;32m"<<yellow<<">>$ "<<green<<" To SIGN IN use                  :"<<cyan<< "  'sign_in username password'\033[0m"<<endl;
    cout<<"\033["<<b+4<<";1H\033[1;32m"<<yellow<<">>$ "<<green<<" To view use                     :"<<cyan<< "  'view'\033[0m"<<endl;
    cout<<"\033["<<b+4<<";1H\033[1;32m"<<yellow<<">>$ "<<green<<" To delete use                   :"<<cyan<< "  'delete filename .extension'\033[0m"<<endl;
    }










void filter(vector<string> v)
{
  system("clear");
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
    // cout<<"\033["<<b  <<";1H\033[1;32m>>$To create a private ACCOUNT use : 'account username password'\033[0m"<<endl;
    // cout<<"\033["<<b+1<<";1H\033[1;32m>>$To UPLOAD use                   : 'upload filename extension'\033[0m"<<endl;
    // cout<<"\033["<<b+2<<";1H\033[1;32m>>$To DOWNLOAD use                 : 'download filename extension'\033[0m"<<endl;
    // cout<<"\033["<<b+3<<";1H\033[1;32m>>$To SIGN IN use                  : 'sign_in username password'\033[0m"<<endl;
    // cout<<"\033["<<b+4<<";1H\033[1;32m>>$To view use                     : 'view'\033[0m"<<endl;
    // cout<<"\033["<<b+4<<";1H\033[1;32m>>$To delete use                   : 'delete filename .extension'\033[0m"<<endl;


    cout<<"\033["<<b  <<";1H\033[1;32m"<<yellow<<">>$ "<<green<<" To create a private ACCOUNT use :"<<cyan<< "  'account username password'\033[0m"<<endl;
    cout<<"\033["<<b+1<<";1H\033[1;32m"<<yellow<<">>$ "<<green<<" To UPLOAD use                   :"<<cyan<< "  'upload filename extension'\033[0m"<<endl;
    cout<<"\033["<<b+2<<";1H\033[1;32m"<<yellow<<">>$ "<<green<<" To DOWNLOAD use                 :"<<cyan<< "  'download filename extension'\033[0m"<<endl;
    cout<<"\033["<<b+3<<";1H\033[1;32m"<<yellow<<">>$ "<<green<<" To SIGN IN use                  :"<<cyan<< "  'sign_in username password'\033[0m"<<endl;
    cout<<"\033["<<b+4<<";1H\033[1;32m"<<yellow<<">>$ "<<green<<" To view use                     :"<<cyan<< "  'view'\033[0m"<<endl;
    cout<<"\033["<<b+4<<";1H\033[1;32m"<<yellow<<">>$ "<<green<<" To delete use                   :"<<cyan<< "  'delete filename .extension'\033[0m"<<endl;
    if (CURRENT_USERNAME!="")
    {
      printf("\n\n\ncurrent username    " );
      std::cout << CURRENT_USERNAME << "\n";
      printf("\nCurrent memory   " );
      std::cout << MEMORY_LET << '\n';
    }

  }








































void catch_ctrl_c_and_exit(int sig) {
    flag = 1;
}


int main(int argc, char *argv[])
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
    char *serverIp = argv[1];

    struct hostent* host = gethostbyname(serverIp) ;

    struct hostent *server;
    int s_addrlen = sizeof(server_info);
    int c_addrlen = sizeof(client_info);
    memset(&server_info, 0, s_addrlen);
    memset(&client_info, 0, c_addrlen);
    bzero((char *) &server_info, sizeof(server_info));
    // server_info.sin_family = PF_INET;
    server_info.sin_family = AF_INET;
    // server_info.sin_addr.s_addr = inet_addr("127.0.0.1");

    // server = gethostbyname(argv[1]);
    // server_info.sin_addr.s_addr = inet_addr("127.0.0.1");
    // bcopy((char *)server->h_addr,  (char *)&server_info.sin_addr.s_addr,  server->h_length);
    server_info.sin_port = htons(8888);
    server_info.sin_addr.s_addr =  inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
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
    string privaetdaat1 = "";
    string privaetdaat2 = "";
    //recieving menu
    SHOW_BASE_DES();//basic design
    // std::cout << "----------------------------WELCOME TO DROPSHIT-----------------------" << '\n'<<endl<<endl;
    recv(sockfd,&receivemenulength1,sizeof(int),0 );
    // recv(sockfd,menu,sizeof(char)*receivemenulength1,0 );
    // std::cout << "menu leght"<<receivemenulength1 << '\n';
    recv_throughsocket(menu,receivemenulength1,sockfd);
    std::vector<string> v3;
    std::vector<string> v2;
    std::vector<string> v1 = split(menu,"\n");
    filter(v1);
    // printf("\n%s\n",menu);

    while (1)
    {
          printf("\n>> " );
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
            {
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
            }
              recv(sockfd,&recievemainmessagestrlength,sizeof(int),0);
              // recv(sockfd,recievemainmessage,recievemainmessagestrlength*sizeof(char),0);
              recv_throughsocket(recievemainmessage,recievemainmessagestrlength,sockfd);


              // std::cout << recievemainmessage << '\n';
                v1 = split(chartostring(recievemainmessage,recievemainmessagestrlength),"\n");
              // filter(v1);
              // if (SIGN_IN_FLAG==1)
              // {
              //   printf("You are logged in \n" );
              //   // cout<<v1;
              //   int fagl_close = -2;
              //   v1 = split(chartostring(recievemainmessage,recievemainmessagestrlength),"\n");
              //   for (int tom = 0; tom < v1.size(); tom++)
              //   {
              //     std::cout << v1[tom] << '\n';
              //     if (v1[tom].compare("private.txt")==0)
              //     {
              //       fagl_close ==1;
              //
              //     }
              //     if (fagl_close==-2)
              //     {
              //       privaetdaat1+=v1[tom];
              //       privaetdaat1+="\n";
              //
              //
              //     }
              //     if (fagl_close==1)
              //     {
              //       if (v1[tom].compare("private.txt")!=0)
              //       {
              //         privaetdaat2+=v1[tom];
              //         privaetdaat2+="\n";
              //
              //         /* code */
              //       }
              //
              //
              //
              //     }
              //     // privaetdaat+=v1[tom];
              //   }
              //   scanf("%d",&c1);
              //
              //   std::cout << privaetdaat1 << '\n';
              //   scanf("%d",&c1);
              //
              //   std::cout << privaetdaat2 << '\n';
              //   scanf("%d",&c1);
              //
              //   v2 = split(privaetdaat1,"\n");
              //
              //   // v2 = split(privaetdaat,"private.txt");
              //
              //   scanf("%d",&c1);
              //   for (int tom = 0; tom < v1.size(); tom++)
              //   {
              //     std::cout << v3[tom] << '\n';
              //
              //     // privaetdaat+=v1[tom];
              //   }
              //
              //   scanf("%d",&c1);
              //
              //   for (int tom = 0; tom < v1.size(); tom++)
              //   {
              //     std::cout << v2[tom] << '\n';
              //     // privaetdaat+=v1[tom];
              //   }
              //   scanf("%d",&c1);
              //
              //
              // }


              char s[1500];
              strcpy(s,recievemainmessage);
              // cout<<"\n print s array: "<<s;


              string viewlist = chartostring(s,strlen(s));
            //   printf("\n viewlist: %s",viewlist.c_str());
                // cout<<"\n viewlist:  "<<viewlist;
                // cout<<"\n end of viewlist"<<endl;       //printing some values after end of viewlist

              vector<string> choi = split1(viewlist);
              // cout<<"\n choic carray: "<<endl;
              int k;
              for(k = 0;k<choi.size();k++)    //working
              {
                choices[k] = choi[k].c_str();
                // cout<<choices[k]<<" ";

              }
              choices[k] = NULL;
                // cout<<choi[i]<<" ";

              cout<<endl;

            // int n = ARRAY_SIZE(s);
            // for(int i =0;i<n;i++)
            //   cout<<s[i]<<" ";
            //   cout<<endl;



            /*
                printing properly
            cout<<"\n Enter choices array: ";

            int n = ARRAY_SIZE(choices);
            for(int i =0;i<n;i++)
              cout<<choices[i]<<" ";
              cout<<endl;
              */


            ITEM **my_items;
            int c;
            MENU *my_menu;
                  WINDOW *my_menu_win;
                  int n_choices, i;

  /* Initialize curses */
        initscr();

        init_pair(1,COLOR_BLACK, COLOR_MAGENTA);



                attron(A_BOLD);

                attron(COLOR_PAIR(1));

                // attron(A_STANDOUT);

                attron(A_UNDERLINE);



                mvprintw(2, 5, "%s", "NIMBUS");



                // attroff(A_STANDOUT);

                attroff(A_UNDERLINE);

                attroff(COLOR_PAIR(1));

                attroff(A_BOLD);


        // start_color();

              cbreak();
              noecho();
        keypad(stdscr, TRUE);
        // init_pair(1, COLOR_RED, COLOR_BLACK);
        // init_pair(2, COLOR_CYAN, COLOR_BLACK);

        /* Create items */
              n_choices = ARRAY_SIZE(choices);
              my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
              for(i = 0; i < n_choices; ++i)
                      my_items[i] = new_item(choices[i], choices[i]);

        /* Crate menu */
        my_menu = new_menu((ITEM **)my_items);

        /* Set menu option not to show the description */
        menu_opts_off(my_menu, O_SHOWDESC);

        /* Create the window to be associated with the menu */
              my_menu_win = newwin(10, 70, 4, 4);
              keypad(my_menu_win, TRUE);

        /* Set main window and sub window */
              set_menu_win(my_menu, my_menu_win);
              set_menu_sub(my_menu, derwin(my_menu_win, 6, 68, 3, 1));
        set_menu_format(my_menu, 5, 3);
        set_menu_mark(my_menu, " * ");
        refresh();

        /* Print a border around the main window and print a title */
              char top = '-';
              char bottom = '-';
              char right = '|';
              char left = '|';
              char corner = '+';
              // char left
              // box(my_menu_win, 0,0);
              wborder(my_menu_win,(int)left, (int)right,(int)top, (int)bottom,(int)corner,(int)corner,(int)corner,(int)corner);

        // attron(COLOR_PAIR(2));
        /* Make the menu multi valued */
            menu_opts_off(my_menu, O_ONEVALUE);

          mvprintw(LINES - 4, 0, "Use <SPACE> to select or unselect an item.");
          mvprintw(LINES - 3, 0, "<ENTER> to see presently selected items(F1 to Exit)");
        mvprintw(LINES - 2, 0, "Use PageUp and PageDown to scroll");
        // mvprintw(LINES - 2, 0, "Use Arrow Keys to navigate (F1 to Exit)");
        // attroff(COLOR_PAIR(2));
        refresh();

        /* Post the menu */
        post_menu(my_menu);
        wrefresh(my_menu_win);

        while((c = wgetch(my_menu_win)) != KEY_F(1))
        {       switch(c)
                {	case KEY_DOWN:
              menu_driver(my_menu, REQ_DOWN_ITEM);
              break;
            case KEY_UP:
              menu_driver(my_menu, REQ_UP_ITEM);
              break;
            case KEY_LEFT:
              menu_driver(my_menu, REQ_LEFT_ITEM);
              break;
            case KEY_RIGHT:
              menu_driver(my_menu, REQ_RIGHT_ITEM);
              break;
            case KEY_NPAGE:
              menu_driver(my_menu, REQ_SCR_DPAGE);
              break;
            case KEY_PPAGE:
              menu_driver(my_menu, REQ_SCR_UPAGE);
              break;

              case ' ':
                      menu_driver(my_menu, REQ_TOGGLE_ITEM);
                      break;

              case 10:	/* Enter */
                    {	char temp[200];
                      ITEM **items;

                      items = menu_items(my_menu);
                      temp[0] = '\0';
                      for(i = 0; i < item_count(my_menu); ++i)
                        if(item_value(items[i]) == TRUE)
                        {	strcat(temp, item_name(items[i]));
                          strcat(temp, " ");
                        }
                      move(20, 0);
                      clrtoeol();
                      mvprintw(20, 0, temp);
                      strcpy(dfile,temp);
                      refresh();
          }
          break;
              }
                          wrefresh(my_menu_win);
            }

        /* Unpost and free all the memory taken up */
              unpost_menu(my_menu);
              free_menu(my_menu);
              for(i = 0; i < n_choices; ++i)
                      free_item(my_items[i]);
            endwin();

              filter(v1);

              cout<<"\n your choice is: "<<dfile;
              cout<<"\n\n";










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
              recv(sockfd,&MEMORY_LET,sizeof(float),0);

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
              std::cout << "CUURENT USSERNAME " <<CURRENT_USERNAME<< '\n';
              std::cout << "CUURENT memory left " <<MEMORY_LET<< '\n';

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
              CURRENT_USERNAME = "";
              MEMORY_LET = -1;
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
              int ch23;
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
                 // ch23 = 3;
                 // send(sockfd, &ch23, sizeof(ch23),0); //strlen(ch23)
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

          else if (parsedcommand.command_name=="download")
          {

                printf("Reached download\n" );
                string path = "";
                string nameof = "";
                int checkclientfolder = -1;
                // std::cout << "path of server "<<path << '\n';
                nameof = parsedcommand.info1+"."+parsedcommand.info2;
                path = download_path+parsedcommand.info1+"."+parsedcommand.info2;
                        printf("\nCheck name=\n" );
                        std::cout << nameof << '\n';
                        std::cout << path << '\n';
                char path1[path.length()+1] ;
                strcpy(path1,path.c_str());
                int success1 = -1;
                int bytesRead, bytesWritten = 0;
                 fstream f2;
                 int ch23;

               // f2.open("New.mp4", ios::out);
               recv(sockfd,&success1,sizeof(int),0);
               if (success1)
               {
                std::cout << "Failed "<<" No such file" << '\n';
               }
              else
               {
              f2.open(path1, ios::out);
              checkclientfolder = f2.fail();

               while((recv(sockfd, &ch23, sizeof(ch23), 0)>0))
               {

              // printf("%c\n",ch23 );
              // printf("%d\n",ch23 );

              if (ch23==-1)
              {
                printf("end" );
                  break;
              }
              if (checkclientfolder==0)
              {

                f2.put(ch23);
              }


               }
               if (checkclientfolder==0)
               {
                 cout<<"\n file received \n";
               }
                else{
                  std::cout << "file already exist" << '\n';
                }
               f2.close();

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
