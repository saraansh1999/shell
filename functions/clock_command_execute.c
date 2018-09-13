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
int run=1;

/*void local_signal_handler(int sig)
{
	printf("\nStopped.\n");
	run=0;
}
*/

void clock_command_execute(char ** args)
{
	FILE* fd;
	char data[3003],end;
	int interval=atoi(args[2]);

	signal(SIGINT,clock_signal_handler);

	while(run)
	{
		sleep(interval);
		fd=fopen("/sys/class/rtc/rtc0/date","r");
		if(fd==NULL)
		{
			fprintf(stderr, "ERROR : Data can't be received.\n");
			exit(EXIT_FAILURE);
		}
		while(fgets(data,3000,fd)!=NULL)
		{
			data[strlen(data)-1]=',';
			printf("%s ",data);
		}
		fclose(fd);

		fd=fopen("/sys/class/rtc/rtc0/time","r");
		if(fd==NULL)
		{
			fprintf(stderr, "ERROR : Data can't be received.\n");
			exit(EXIT_FAILURE);
		}
		while(fgets(data,3000,fd)!=NULL)
		{
			printf("%s",data);
		}
		fclose(fd);
	}

	exit(EXIT_SUCCESS);
}