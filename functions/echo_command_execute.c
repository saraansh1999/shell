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


void echo_command_execute(char* command)
{
	int flag=0,i=4,qoutes=0,one=0;
	for(;command[i]!='\0';i++)
	{
		if(command[i]=='\"')
		{
			if(command[i-1]!='\\')
				qoutes++;
		}
	}
	if(qoutes%2!=0)
	{
		fprintf(stderr,"Unmatched qoutations\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		i=5;
		for(;command[i]!='\0';i++)
		{
			if(isspace(command[i]))
			{
				if(flag==1)
					printf("%c",command[i]);
				else if(one==0)
				{
					printf(" ");
					one=1;
				}
			}
			else if(command[i]=='\\')
			{
				i++;
				if(command[i]=='\"')
					printf("\"");
				else if(command[i]=='n')
					printf("\n");
				else if(command[i]=='\\')
					printf("\\");
				one=0;
			}
			else if(command[i]=='\"')
			{
				one=0;
				flag=flag^1;
			}
			else
			{
				one=0;
				printf("%c",command[i]);
			}
		}
		printf("\n");
	}
	exit(EXIT_SUCCESS);
}