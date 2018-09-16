#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include "../definitions.h"


extern bg_processes bgpro[1005];


void overkill_command_execute()
{
	int i,f=0;
	for(i=0;i<1005;i++)
	{
		if(bgpro[i].pid!=-1)
		{
			if(kill(bgpro[i].pid,SIGKILL)==-1)
			{
				printf("ERROR : %s with pid [%d] was not killed successfully.\n",bgpro[i].name,bgpro[i].pid );
				f++;
			}
		}
	}
	if(f==0)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}