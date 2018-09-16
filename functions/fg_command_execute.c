#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include "../definitions.h"


extern int curr_fg;


void fg_command_execute(char ** args)
{
	int pid,status;

	if(args[1]==NULL || args[2]!=NULL)
	{
		printf("ERROR : Command format is -- fg<jobNumber>\n");
		return;
	}

	sscanf(args[1],"%d",&pid);

	if(kill(pid,SIGSTOP)==-1)
	{
		printf("ERROR : Foregrounding failed\n");
		return;	
	}
	if(kill(pid,SIGCONT)==-1)
	{
		printf("ERROR : Foregrounding failed\n");
		return;
	}

	curr_fg=pid;
	printf("%d foregrounded\n",pid );

	do
	{
		waitpid(pid,&status,WUNTRACED);
		if(WIFSTOPPED(status))
		{
			bg_after_fg(pid);
			break;
		}
	}
	while(!WIFEXITED(status) && !WIFSIGNALED(status));

	return;
}