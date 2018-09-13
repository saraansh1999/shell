#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<signal.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include "../definitions.h"


extern int close_shell;
extern char root[1005];
extern char relative_curr_dir[1005];
extern char delim[10];
extern int shell_id;
extern bg_processes bgpro[1005];


char** arg_break(char* comm,int bg,int size)
{
	char** args=(char**)malloc((size+5)*sizeof(char*));
	char* command=(char*)malloc((size+5)*sizeof(char));
	strcpy(command,comm);
	int len=strlen(command),i=0;
	char* ptrptr;
	
	
	args[0]=strtok_r(command,delim,&ptrptr);
	while(args[i]!=NULL)
	{
		i++;
		args[i]=strtok_r(NULL,delim,&ptrptr);
	}

	return args;
}


void command_execute(char* comm,int bg,int size)
{
	char** args=(char**)malloc((size+5)*sizeof(char*));
	int pid,i=0,j,status,wpid,len=strlen(comm);
	if(bg==1)
	{
		comm[--len]='\0';
	}
	args=arg_break(comm,bg,size);
	char* command=(char*)malloc((size+5)*sizeof(char));
	strcpy(command,comm);

	if(strncmp(command,"remindme",8)==0)
		bg=1;

	if(strncmp(command,"cd",2)==0 && bg==0)
	{
		cd_command_execute(args,1);
	}
	else if(strncmp(command,"pinfo",5)==0 && bg==0)
	{
		pinfo_command_execute(args,1);
	}
	else if(strncmp(command,"exit",4)==0)
		close_shell=1;
	else
	{
		pid=fork();

		if(pid==0)
		{
			if(strncmp(command,"cd",2)==0)
			{
				cd_command_execute(args,pid);
			}
			else if(strncmp(command,"ls",2)==0)
			{
				ls_command_execute(args,size+5);
			}
			else if(strncmp(command,"pwd",3)==0)
			{
				pwd_command_execute(args);
			}
			else if(strncmp(command,"echo",4)==0)
			{
				echo_command_execute(command);
			}
			else if(strncmp(command,"pinfo",5)==0)
			{
				pinfo_command_execute(args,pid);
			}
			else if(strncmp(command,"remindme",8)==0)
			{
				remindme_command_execute(args);
			}
			else if(strncmp(command,"clock",5)==0)
			{
				clock_command_execute(args);
			}
			else
			{
				system_command_execute(args);
			}

		}
		else
		{
			if(bg==0)
			{
				do
				{
					wpid=waitpid(pid,&status,WUNTRACED);
				}
				while (!WIFEXITED(status) && !WIFSIGNALED(status));
			}
			if(bg==1)
			{
				for(i=0;i<1005;i++)
				{
					if(bgpro[i].pid==-1)
					{
						bgpro[i].pid=pid;
						strcpy(bgpro[i].name,args[0]);
						break;
					}
				}
				printf("[%d]\n", pid);
			}
		}
	}
	
	free(args);
	//printf("freed\n");
	free(command);
	//printf("freed\n");
	return;

}
