#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include<sys/wait.h> 
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

void mkdir_command(char const *str,int simple,char const *flag)
{
	if(simple==1)
	{
		int ret=mkdir(str,0700); // with read/write/search permissions for owner and group, and with read/search permissions for others.
		if(ret<0)
		{
			perror("Error in directory creation");
		}
	}
	else{
		if(!(strcmp(flag,"-v\n")) || !(strcmp(flag,"-v")))
		{
			int ret=mkdir(str,0700); // with read/write/search permissions for owner and group, and with read/search permissions for others.
			if(ret<0)
			{
				perror("Error in directory creation");
			}
			printf("%s:\t%s'%s'\n","mkdir","created directory ",str);
		}
		if(!(strcmp(flag,"-p\n")) || !(strcmp(flag,"-p")))
		{	
			char *pointer1=str;
			char *pointer=strtok(pointer1,"/");
			while(pointer!=NULL)
			{
				int ret=mkdir(pointer,0700); // with read/write/search permissions for owner and group, and with read/search permissions for others.
				if(ret<0)
				{
					perror("Error in directory creation");
				}

				char str[1024];
  				getcwd(str,1024);
  				strcat(str,"/");
  				strcat(str,pointer);

				 int val= chdir(str);
				 if(val<0)
				 {
				 	perror("Error in directory change ");
				 }
				 getcwd(str,1024);
				 
				 pointer=strtok(NULL,"/");
			}
		}
		else{
			printf("%s\n","command not found");
		}
	}
}
int main(int argc, char const *argv[])
{

	int simple=atoi(argv[1]);
	if(simple==1)
	{
		mkdir_command(argv[0],1,NULL);
	}
	else{
		mkdir_command(argv[0],0,argv[2]);
	}
	
}