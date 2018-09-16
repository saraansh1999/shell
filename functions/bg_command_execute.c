#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include "../definitions.h"


void bg_command_execute(char ** args)
{
	int pid,status;

	if(args[1]==NULL || args[2]!=NULL)
	{
		printf("ERROR : Command format is -- bg<jobNumber>\n");
		return;
	}

	sscanf(args[1],"%d",&pid);

	if(kill(pid,SIGTSTP)==-1)
	{
		printf("ERROR : Backgrounding failed\n");
		return;	
	}
	if(kill(pid,SIGCONT)==-1)
	{
		printf("ERROR : Backgrounding failed\n");
		return;
	}

	printf("%d backgrounded\n",pid );

	return;
}

void bg_after_fg(int pid)
{

	if(kill(pid,SIGTSTP)==-1)
	{
		printf("ERROR : Backgrounding failed\n");
		return;	
	}

	return;
}