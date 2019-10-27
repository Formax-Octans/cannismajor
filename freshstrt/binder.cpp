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

void binder(dataset ds)
{
    string c_name = ds.command_name;
    if(c_name.compare("upload"))
    {
        if(ds.status == 1)
        {
            /*
            enter the query here for upload
            */
        }
        
    }
    else if(c_name.compare("download"))
    {
        if(ds.status == 1)
        {
            /*
            enter the query here for download
            */
        }
    }
    else if(c_name.compare("account"))
    {
        if(ds.status == 1)
        {
            /*
            enter the query here for account
            */
        }
    }
    else if(c_name.compare("sign_in"))
    {
        if(ds.status == 1)
        {
            /*
            enter the query here for sign_in
            */
        }
    }
    else if(c_name.compare("delete"))
    {
        if(ds.status == 1)
        {
            /*
            enter the query here for delete
            */
        }
    }
    else if(c_name.compare("view"))
    {
        if(ds.status == 1)
        {
            /*
            enter the query here for view
            */
        }
    }
    else
    {
        printf("NOT FOUND\n");
    }
    
}