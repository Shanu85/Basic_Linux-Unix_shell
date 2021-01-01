#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include<sys/wait.h> 
#include <string.h>
#include <time.h>

void print_date(struct tm *time_pointer) // for printing global and local time
{
    char buf[256]={0};
       strftime(buf,256,"%A",time_pointer); //National full weekday name
       printf("%s\t",buf);

       printf("%d\t", time_pointer->tm_mday); //the day of the month

       memset(buf,0,256);
       strftime(buf,256,"%B",time_pointer); //National full month name
       printf("%s\t",buf);

       memset(buf,0,256);
       strftime(buf,256,"%Y",time_pointer); //Year
       printf("%s\t",buf);

       memset(buf,0,256);
       strftime(buf,256,"%r",time_pointer); //12-hour clock time
       printf("%s\t",buf);

       memset(buf,0,256);
       strftime(buf,256,"%Z",time_pointer); //Timezone name
       printf("%s\n",buf);
}
int date_command(char const *str,int simple)
{
    time_t tim=time(NULL);
       if(tim==-1)
       {
        perror("Time falied");
        return 1;
       } 
    if(simple)
    {
        struct tm *time_pointer=localtime(&tim);
       if(time_pointer==NULL)
       {
        perror("struct tm falied in localtime");
        return 1;
       }
       print_date(time_pointer);
       
    }
    else
    {
        if(!strcmp(str,"-u\n") || !strcmp(str,"-u"))
        {
            struct tm *UTC_timePointer = gmtime(&tim);
            if(UTC_timePointer==NULL)
               {
                perror("struct tm falied in gmtime");
                return 1;
               }
            print_date(UTC_timePointer);
        }

        else if(!strcmp(str,"-I\n") || !strcmp(str,"-I"))
        {
            struct tm *time_pointer=localtime(&tim);
           if(time_pointer==NULL)
           {
            perror("struct tm falied in localtime");
            return 1;
           }
           char buf[256]={0};
           strftime(buf,256,"%F",time_pointer); //National full month name
           printf("%s\n",buf);
           memset(buf,0,256);
        }
        else{
          printf("%s\n","no such command in date");
        }
    }
}
int main(int argc, char const *argv[])
{
	int i=atoi(argv[1]);
	if(i==1)
	{
		date_command(NULL,i);
	}
	else{
		date_command(argv[0],0);
	}

	return 0;
}