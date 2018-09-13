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


void put_prompt()
{
	char* username;
	char system_name[1005];
	char curr_dir[1005];

	username=getenv("USER");
	gethostname(system_name,1000);
	getcwd(curr_dir,1000);
	relative_curr_dir_generator(curr_dir);

	printf("<%s@%s:%s> ",username,system_name,relative_curr_dir);

	return ;
}