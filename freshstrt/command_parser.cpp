#include<iostream> 
#include<stdio.h>
#include<string> // for string class 
#include<string.h>
#include<vector>
using namespace std; 

struct dataset
{
   string info1;
   string info2; 
   string command_name;
   int status = 0;
};

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

dataset parser()
{
    string command;
    cout << "Please enter \n"; 
    getline (cin, command); 
    
    vector<string> words;
    words = split(command," ");
    int n = words.size();
    // for (int i = 0;i<n;i++)
    // {
    //     cout << words[i] << endl;
    // }
    //datset initialisation
    dataset ds;
    //for account set up
    if(words[0].compare("account")==0)
    {
        
        ds.info1 = words[1];
        ds.info2 = words[2];
        ds.command_name = "account";
        ds.status = 1;
    }
    else if(words[0].compare("sign_in")==0)
    {
        
        ds.info1 = words[1];
        ds.info2 = words[2];
        ds.command_name = "sign_in";
        ds.status = 1;
    }
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

int main()
{
    dataset d;
    d = parser();
    cout << d.command_name;
    return 0;
}
