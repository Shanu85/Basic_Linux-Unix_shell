#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include<sys/wait.h> 
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

void rm_command(int simple,char const *str,char const *flag)
{
	if(simple)
	{
		int del = remove(str);
	   	if(del!=0)
	   	{
	   		perror("Cannot remove file ");
	   	}
	}
	else
	{
		if(!(strcmp(flag,"-f\n")) || !(strcmp(flag,"-f")))
		{
			int del=remove(str);
		}
		else if(!(strcmp(flag,"-i\n")) || !(strcmp(flag,"-i")))
		{
			FILE *file;
			file = fopen(str, "r");
			if(file!=NULL)
			{
				printf("%s '%s' %s:","do you want to remove file",str,"?");
				char string[100];
				fgets(string,100,stdin);
				if(!(strcmp(string,"y") ) || !(strcmp(string,"y\n")))
				{
					int del=remove(str);
					if(del!=0)
				   	{
				   		perror("Cannot remove file ");
				   	}
				}
			}
			else
			{
				printf("%s\n","no such file exists ");
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
		rm_command(1,argv[0],NULL);
	}
	else{
		rm_command(0,argv[0],argv[2]);
	}
	
}