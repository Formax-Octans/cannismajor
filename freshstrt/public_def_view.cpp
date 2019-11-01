#include<iostream> 
#include<stdio.h>
#include<algorithm>
#include<string> // for string class 
#include<string.h>
#include<vector>
#include<unistd.h>
using namespace std; 

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
    cout<<"\033["<<b+1<<";1H\033[1;32m>>$To UPLOAD use                   : 'upload filename .extension'\033[0m"<<endl;
    cout<<"\033["<<b+2<<";1H\033[1;32m>>$To DOWNLOAD use                 : 'download filename .extension'\033[0m"<<endl;
    cout<<"\033["<<b+3<<";1H\033[1;32m>>$To SIGN IN use                  : 'sign_in username password'\033[0m"<<endl;
    cout<<"\033["<<b+4<<";1H\033[1;32m>>$To view use                     : 'view'\033[0m"<<endl;
    cout<<"\033["<<b+4<<";1H\033[1;32m>>$To delete use                   : 'delete filename .extension'\033[0m"<<endl;
    }
int main()
{
    vector<string> vec{"1.txt","2.txt","3.txt","4.txt","5.txt","6.txt","7.txt","8.txt","9.txt","10.txt","two.pdf","sexy.txt","fuck.pdf","mia.mp4","sunny.mp4","addams.mp4","bianca.mp4","ritvik.chu","sot.mp3","chakachk.mp3","love.jpeg","chut.png","parth.txt","boby.mp3","sun.png","moon.bmp","lola.pdf","porn.mp4","maakichu.tja"};
    system("clear");
    filter(vec);
    cout<<"\033[40;1H\n"<<endl;
    //sleep(2);
    return 0;
}