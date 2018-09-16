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
#include "definitions.h"


extern int close_shell;
extern char root[1005];
extern char relative_curr_dir[1005];
extern char delim[10];
extern int shell_id;


int main()
{

	signal(SIGINT,SIGINT_handler);
	signal(SIGTSTP,SIGTSTP_handler);	

	int i;
	getcwd(root,1000);
	
	curr_fg=-1	;
	close_shell=0;
	strcpy(delim," \t\r\n\v\f\a");
	for(i=0;i<1005;i++)
		bgpro[i].pid=-1;

	shell_id=getpid();

	while(!close_shell)
	{

		put_prompt();
		get_command();
		
		check_bg_exit();
	}

	exit(EXIT_SUCCESS);
} 