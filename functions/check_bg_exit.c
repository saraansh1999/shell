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
extern bg_processes bgpro[1005];


void check_bg_exit()
{
	int wpid,status,i;

	while((wpid=waitpid(-1,&status,WNOHANG))>0)
	{
		if(WIFEXITED(status))
		{
			for(i=0;i<1005;i++)
			{
				if(bgpro[i].pid==wpid)
				{
					fprintf(stderr,"[%s with pid %d exited with status %d]\n",bgpro[i].name,wpid,WEXITSTATUS(status));
					bgpro[i].pid=-1;
					break;
				}
					
			}


		}
	}
	return;
}