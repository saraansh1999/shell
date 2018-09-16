#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include "../definitions.h"


extern int curr_fg;


void SIGINT_handler(int sig)
{
	signal(SIGINT,SIGINT_handler);
	if(curr_fg==-1)
		return;
	else
	{
		if(kill(curr_fg,SIGINT)==-1)
		{
			printf("ERROR : Could not stop process with pid [%d]\n",curr_fg);
			return;
		}
	}
	printf("\n");
	return ;
}

void SIGTSTP_handler(int sig)
{
	if(curr_fg==-1)
		return;
	else
	{
		if(kill(curr_fg,SIGTSTP)==-1)
		{
			printf("ERROR : Could not stop process with pid [%d]\n",curr_fg);
			return;
		}
	}
	printf("\n");
	return;
}

void clock_signal_handler(int sig)
{
	signal(SIGINT,SIGINT_handler);
	exit(EXIT_SUCCESS);
}