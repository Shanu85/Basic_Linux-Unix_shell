#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include<sys/wait.h> 
#include <string.h>

void ls_command(char const *str,int simple) // int simple check if it is simple ls or flaged ls
{
    struct dirent **allfile_list;
    int total_files=0;
    total_files = scandir(".",&allfile_list, NULL, alphasort);
    if(total_files<0) // on error, -1 is returned
    {
        perror("scandir");
    }

    else 
    {
        if(simple==1)
        {
            for (int i = 0; i < total_files; ++i)
             {
                char *name=allfile_list[i]->d_name;
                    if(name[0]!='.')
                    {
                        printf("%s\t",name);
                        
                    }  
                    free(allfile_list[i]);   
                 }
                 free(allfile_list);
                   printf("\n");  
        }
        else{
            if(!(strcmp(str,"-a\n")) || !(strcmp(str,"-a")))
            {
                for (int i = 0; i < total_files; ++i)
                 {
                    printf("%s\t",allfile_list[i]->d_name);
                    free(allfile_list[i]);  
                 } 
                   free(allfile_list);
                   printf("\n");
            }
            else if(!(strcmp(str,"-A\n")) || !(strcmp(str,"-A")))
            {
                for (int i = 0; i < total_files; ++i)
                 {
                    char *name=allfile_list[i]->d_name;
                    if(name[0]=='.' && strlen(name)>1)
                    {
                        if(name[1]!='.')
                        {
                            printf("%s\t",name);
                        }
                    }
                    else if(name[0]!='.')
                    {
                        printf("%s\t",name);
                    }
                    free(allfile_list[i]);  
                 } 
                   free(allfile_list);
                   printf("\n");
            }
            else if(!(strcmp(str,"-m\n")) || !(strcmp(str,"-m")))
            {
                for (int i = 0; i < total_files; ++i)
                 {
                    char *name=allfile_list[i]->d_name;
                        if(name[0]!='.')
                        {
                            printf("%s, ",name);
                            
                        }
                        free(allfile_list[i]);     
                     }
                free(allfile_list);
                printf("\n");  
             }
             else{
              printf("%s\n","No such command in ls");
             }
        }
    
    }
}
int main(int argc, char const *argv[])
{
	int i=atoi(argv[1]);
	if(i==1)
	{
		ls_command(NULL,i);
	}
	else{
		ls_command(argv[0],0);
	}

	return 0;
}