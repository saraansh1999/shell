#include<signal.h>
#include<stdlib.h>
#include "../definitions.h"


void global_signal_handler(int sig)
{
	return;
}


void clock_signal_handler(int sig)
{
	signal(SIGINT,global_signal_handler);
	exit(EXIT_SUCCESS);
}