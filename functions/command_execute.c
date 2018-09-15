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
extern int piping[2];
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


void command_execute(char* comm,int bg,int size,int prev,int next)
{
	int found_error=0,ret,fd,pid,i=0,j,status,wpid,len=strlen(comm),out_red=0,in_red=0,last_letter_in,last_letter_out;

	if(prev)
	{
		close(piping[1]);
		close_pipe_out();
		if(receive_from_pipe(&piping[0]))
		{
			found_error=1;
			close(piping[0]);
			close_pipe_in();
		}
	}
	if(next)
	{
		if(pipe(piping)==-1)
		{
			found_error=1;
			printf("ERROR : Piping unsuccessful\n");
		}
		if(send_to_pipe(&piping[1]))
		{
			found_error=1;
		}
	}

	if(bg==1)
	{
		comm[--len]='\0';
	}
	last_letter_in=last_letter_out=len;
	for(i=0;comm[i]!='\0';i++)
	{
		if(comm[i]=='>')
		{
			out_red=1;
			comm[i]=' ';
			if(comm[i+1]!='\0' && comm[i+1]=='>')
			{
				comm[i+1]=' ';
				ret=redirect_to_file(comm,2,i+2,size);
				if(ret)
				{
					found_error=1;
				}
			}
			else
			{
				ret=redirect_to_file(comm,1,i+1,size);
				if(ret)
				{
					found_error=1;
				}
			}
		}
		if(comm[i]=='<')
		{
			in_red=1;
			comm[i]=' ';
			ret=redirect_from_file(comm,i+1,size);
			if(ret)
			{
				found_error=1 ;
			}
		}
	}
	
	if(!found_error)
	{
		char** args=(char**)malloc((size+5)*sizeof(char*));
		char* command=(char*)malloc((size+5)*sizeof(char));
		for(i=0;comm[i]!='\0';i++)
			command[i]=comm[i];
		command[i]='\0'	;
		args=arg_break(command,bg,size);

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
		else if(strncmp(command,"setenv",6	)==0)
		{
			if(args[1]==NULL)
			{
				printf("ERROR : Too few arguements.\n");
				return;
			}
			if(args[3]!=NULL)
			{
				printf("ERROR : Too many arguements.\n");
				return;
			}
			if(args[2]!=NULL)
			{
				setenv(args[1],args[2],1);
			}
			else
			{
				setenv(args[1],"",1);
			}

		}
		else if (strncmp(command,"unsetenv",8)==0)
		{
			if(args[1]==NULL)
			{
				printf("ERROR : Too few arguements.\n");
				return;
			}
			for(i=1;args[i]!=NULL;i++)
			{
				unsetenv(args[i]);
			}
		}
		else if(strncmp(command,"exit",4)==0)
		{
			printf("Exit!\n");
			close_shell=1;
		}
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
					system_command_execute(args,in_red);
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
	}

	if(out_red)
	{
		close_redirection_out();
	}
	if(in_red)
	{	
		close_redirection_in();
	}
	if(next)
	{
		close_pipe_out();
	}
	if(prev)
	{
		close_pipe_in();
	}
	
	return;

}
