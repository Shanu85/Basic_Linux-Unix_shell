#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<unistd.h> 
#include<sys/types.h> 
#include <dirent.h>
#include<sys/wait.h> 
#include <time.h>

void printHistory(char arr[1000][1000],int *counter,char *flag, int position)
{
  if(flag==NULL)
  {
    int count=0;
    for(int i=0;i<=*counter;i++)
    {
      if(arr[i]!=NULL)
      {
        printf("%d  %s",count,arr[i]);
        count++;
      }
    }
  }
  else{
    if(!(strcmp(flag,"-c")) || !(strcmp(flag,"-c\n")))
    {
      for (int i = 0; i <= *counter; i++)
      {
          memset(arr[i],0,1000);
      }
      *counter=0;
    }
    else if(!(strcmp(flag,"-d")) || !(strcmp(flag,"-d\n")))
    {
      for (int i = position; i < *counter; i++)
      {
        for (int j = 0; j < strlen(arr[i+1]); j++)
        {
            arr[i][j]=arr[i+1][j];
        }
      }
      *counter=*counter-1;
    }
    else
    {
      printf("%s\n","no such flag in history");
    }
  }
}

void echo_command(char array[100],int j,int input_length)
{
    if(array[j+1]=='-')
    {
        if(array[j+2]=='e')
        {
            int i=j+4;
            while(i<input_length)
            {
                if(array[i]=='"')
                {
                    i++;
                }
                else
                {
                    if(array[i]=='\\')
                    {
                        if(array[i+1]=='n')
                        {
                            printf("\n");
                        }
                        else if(array[i+1]=='b')
                        {
                            printf("\b");
                        }
                        else if(array[i+1]=='t')
                        {
                            printf("\t");
                        }
                        else if(array[i+1]=='r')
                        {
                            printf("\r");
                        }
                        i++;
                    }
                    else{
                        printf("%c",array[i]);
                    }
                    i++;
                }
            }
        }
        else if(array[j+2]=='n')
        {
            for (int i = j+4; i <input_length-1; i++)
            {

                if(array[i]=='"')
                {
                    continue;
                }
                
                else{
                    printf("%c",array[i]);
                }
            }
        }
    }
    else{
        for (int i = j; i <input_length; ++i)
        {
            if(array[i]=='"'){
                continue;
            }
            printf("%c",array[i]);
        }
    }
}

void pwd_command()
{
  char str[1024];
  getcwd(str,1024);
  printf("%s\n",str);
}

void cd_command(char *pointer,int simple)
{
  if(simple==1){
    char *pointer1=strtok(pointer,"\n");

    chdir(pointer1);

  }
  else{
      chdir("/home");
  }
}
int take_input(char history_arr[1000][1000])
{

    char *username=getenv("USER");
    int counter=0; // counter for history arr

    printf("%s $ ",username);

    while(1)
    {
        char str[100];
        fgets(str,100,stdin);

        strcpy(history_arr[counter],str);
        int input_length=strlen(str);

        char* pointer=strtok(str," ");

        if(!(strcmp(pointer,"history\n")) || !(strcmp(pointer,"history")))
        {
          int length1=strlen(pointer);
            if(length1==input_length)
            {
              printHistory(history_arr,&counter,NULL,0);
            }
            else
            {
              pointer=strtok(NULL," ");
              char *pointer_copy=pointer;
              length1=length1+strlen(pointer);
              if(length1==input_length)
              {
                printHistory(history_arr,&counter,pointer,0);
              }
              else
              {
                pointer=strtok(NULL," ");
                int position=atoi(pointer);
                printHistory(history_arr,&counter,pointer_copy,position);

              }
            }
        }

        else if(!(strcmp(pointer,"exit\n")))
        {
            break;
        }

        else if(!(strcmp(pointer,"echo")) || !(strcmp(pointer,"echo\n")))
        {
            pointer=strtok(NULL," ");
            int count=0;
            while(str[count]!='\0')
            {
                count++;
            }
            echo_command(str,count,input_length);
        }

        else if(!(strcmp(pointer,"cat")) || !(strcmp(pointer,"cat\n")))
        {
            pid_t pid=fork();
            if(pid<0)
            {
              perror("Error in cat child process creation");
              exit(1);
            }
            else if(pid==0){
              int length1=strlen(pointer);
                pointer=strtok(NULL," ");

                length1=length1+strlen(pointer);

                if(length1+1==input_length)
                {
                    char *newPointer=strtok(pointer,"\n");
                    execlp("./catC",pointer,"1",NULL); //pointer store - file name
                }
                else{
                    char *flag=pointer;
                    pointer=strtok(NULL," ");
                    char *newPointer=strtok(pointer,"\n");
                    execlp("./catC",newPointer,"0",flag,NULL); //falg store flag type
                }
            }
            else{
                  waitpid(pid,NULL,0);
            }
        }
        else if(!(strcmp(pointer,"ls")) || !(strcmp(pointer,"ls\n")))
        {
          pid_t pid=fork();
          if(pid<0)
          {
            perror("Error in ls child process creation");
            exit(1);
          }
          else if(pid==0){
              if(strlen(pointer)==input_length)
              {
                  execlp("./lsC",pointer,"1",NULL);
              }
              else{
                  pointer=strtok(NULL," ");
                  execlp("./lsC",pointer,"0",NULL);
              }
          }
          else{
                waitpid(pid,NULL,0);
          }
        }

        else if(!(strcmp(pointer,"date")) || !(strcmp(pointer,"date\n")))
        {
          pid_t pid=fork();
          if(pid<0)
          {
            perror("Error in date child process creation");
          }
          else if(pid==0){
              if(strlen(pointer)==input_length)
              {
                execlp("./dateC",pointer,"1",NULL);
              }
              else{
                  pointer=strtok(NULL," ");
                  execlp("./dateC",pointer,"0",NULL);
              }
          }
          else{
            waitpid(pid,NULL,0);
          }
        }

        else if(!(strcmp(pointer,"pwd\n")) || !(strcmp(pointer,"pwd")))
        {
          pwd_command();
        }

        else if(!(strcmp(pointer,"cd\n")) || !(strcmp(pointer,"cd")))
        {
            if(strlen(pointer)==input_length)
            {
              cd_command(NULL,0);
            }
            else{

              pointer=strtok(NULL," ");
              cd_command(pointer,1);
            }
        }

        else if(!(strcmp(pointer,"mkdir\n")) || !(strcmp(pointer,"mkdir")))
        {
          pid_t pid=fork();
          if(pid<0)
          {
            perror("Error in date child process creation");
          }
          else if(pid==0){
            
              int length1=strlen(pointer);
            pointer=strtok(NULL," ");
            length1=length1+strlen(pointer);

            if(input_length==length1+1)
            {
              
              char *newPointer=strtok(pointer,"\n");
              execlp("./mkdirC",newPointer,"1",NULL); //pointer store directory name
            }
            else{
              
              char *str=pointer;
              pointer=strtok(NULL," ");
              char *newPointer=strtok(pointer,"\n");

              execlp("./mkdirC",newPointer,"0",str,NULL);
            }
          }
          else{
            waitpid(pid,NULL,0);
          }
            
        }

        else if(!(strcmp(pointer,"rm\n")) || !(strcmp(pointer,"rm")))
        {
          pid_t pid=fork();
          if(pid<0)
          {
            perror("Error in date child process creation");
          }
          else if(pid==0){
            
              int length1=strlen(pointer);
            pointer=strtok(NULL," ");
            length1=length1+strlen(pointer);

            if(input_length==length1+1)
            {
              
              char *newPointer=strtok(pointer,"\n");
              execlp("./rmC",newPointer,"1",NULL); //pointer store directory name
            }
            else{
              
              char *str=pointer;
              pointer=strtok(NULL," ");
              char *newPointer=strtok(pointer,"\n");

              execlp("./rmC",newPointer,"0",str,NULL);
            }
          }
          else{
            waitpid(pid,NULL,0);
          }
        }
        else{
            printf("%s\n","command not found");
        }
        counter++;
        printf("%s $ ",username);

    }
  

}
int main()
{
  char arr[1000][1000];
  take_input(arr);

  return 0;
}