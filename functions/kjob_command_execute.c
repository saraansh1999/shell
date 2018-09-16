#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include "../definitions.h"


void kjob_command_execute(char** args)
{
	int pid,sig;

	if(args[1]==NULL || args[2]==NULL || args[3]!=NULL)
	{
		printf("ERROR : Command format is -- kjob<jobNumber(int)><signalNumber(int)>\n");
		exit(EXIT_FAILURE);
	}

	sscanf(args[1],"%d",&pid);
	sscanf(args[2],"%d",&sig);

	if(kill(pid,sig)==-1)
	{
		printf("ERROR : Signal passing failed\n");
		exit(EXIT_FAILURE);
	}

	printf("%d passed with signal %d!\n",pid,sig );
	exit(EXIT_SUCCESS);
}