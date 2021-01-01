#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include<fcntl.h> 
#include<errno.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include <fcntl.h>

int find_char(char data[1])  // find it character is new line or end of line
{
	if(data[0]=='\n'| data[0]=='\0'){
		return 1;
	}
	return 0;
}

void cat_command(char const *str,int simple,char const *flag)
{
	int file=open(str,O_RDONLY);
		if(file<0)
		{
			perror("Error in file opening");
			exit(1);
		}
		char data[1];
		char arr[1000];

	if(simple==1){
		int j=0;
		while(1)
		{
			read(file,data,1);
			if(find_char(data)==1) 
		  		{
			  		j=0;
			 
			  		printf("%s",arr);
			  		memset(arr, 0, sizeof(arr));
		  		}
		  		if(data[0]=='\0'){  // end of file
					break;
				}
		  		else
		  		{
		  			arr[j]=data[0];
		  			j++;
		  			memset(data, 0, sizeof(data));
		  		}

		}
	}
	else{
		if(!(strcmp(flag,"-E")) || !(strcmp(flag,"-E\n")))
		{
			int j=0;
			while(1)
			{
				read(file,data,1);
				if(find_char(data)==1) 
			  		{
				 		arr[j]='$';
				  		printf("%s",arr);
				  		j=0;
				  		memset(arr, 0, sizeof(arr));
			  		}
			  		if(data[0]=='\0'){  // end of file
						break;
					}
			  		else
			  		{
			  			arr[j]=data[0];
			  			j++;
			  			memset(data, 0, sizeof(data));
			  		}

			}
		}
		else if(!(strcmp(flag,"-T")) || !(strcmp(flag,"-T\n")))
		{
			int j=0;
			while(1)
			{
				read(file,data,1);
				if(find_char(data)==1) 
			  		{
				  		printf("%s",arr);
				  		j=0;
				  		memset(arr, 0, sizeof(arr));
			  		}
			  		
			  		if(data[0]=='\0'){  // end of file
						break;
					}
			  		else
			  		{
			  			if(data[0]=='\t')
			  			{
			  				arr[j]='^';
			  				arr[j+1]='I';
			  				j=j+1;
			  			}
			  			else{
			  				arr[j]=data[0];
			  			}
			  			j++;
			  			memset(data, 0, sizeof(data));
			  		}

			}
		}
		else{
			printf("%s\n","not found such command");
		}
	}
	close(file);
}
int main(int argc, char const *argv[])
{

	int simple=atoi(argv[1]);

	if(simple==1)
	{
		cat_command(argv[0],1,NULL);
	}
	else
	{
		cat_command(argv[0],0,argv[2]);
	}
	

	return 0;
}