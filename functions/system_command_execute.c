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


void system_command_execute(char** args,int red)
{
	execvp(args[0],args);
	printf("ERROR in executing '%s' command\n",args[0]);
	return;
}