//#define _POSIX_SOURCE

#include <unistd.h>
//#undef _POSIX_SOURCE
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
//#include<cstring>

using namespace std;

int main() 
{
//string str1;
  char cwd[256];
char *c1;
std::string str1 = "";
    if (getcwd(cwd, sizeof(cwd)) == NULL)
      perror("getcwd() error");
    else
      printf("current working directory is: %s\n", cwd);

c1 = get_current_dir_name() ;
  // malloc(sizeof(char))
printf("%s ",c1);
free(c1);
for(int i=0;i<strlen(c1);i++)
{
	str1 += c1[i];
}
//strcpy(str1,c1.c_str());
std::cout<<str1;

return 0;

}
