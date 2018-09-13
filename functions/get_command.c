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


void get_command()
{
	//printf("get enter\n");
	int read_size=1005,i=0,no_commands=1;
	char* command=(char*)malloc(read_size*sizeof(char));
	char c;
	while(1)
	{
		c=getchar();

		if(c=='\n')
		{
			command[i]='\0';
			break;
		}
		else if(c==';')
		{
			command[i++]=c;
			no_commands++;
		}	
		else
		{
			command[i++]=c;
		}

		if(i>read_size)
		{
			read_size+=1005;
			command=realloc(command,read_size);
		}
	}
	//printf("%d\n",read_size);
	break_up_command(command,no_commands,read_size);
	free(command);
	return;

}