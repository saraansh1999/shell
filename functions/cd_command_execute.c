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


void cd_command_execute(char** args,int pid)
{
	int ret;

	if(args[1]==NULL || strcmp(args[1],"~")==0)
	{	
		ret=chdir(root);
	}
	else
	{
		ret=chdir(args[1]);
	}
	if(ret!=0)
	{
		fprintf(stderr,"Directory not found\n");
		if(!pid)
			exit(EXIT_FAILURE);
		else
			return;
	}
	else
		if(!pid)
			exit(EXIT_SUCCESS);
		else
			return;
}