#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../definitions.h"


extern int close_shell;
extern char root[1005];
extern char relative_curr_dir[1005];
extern char delim[10];
extern int shell_id;


void relative_curr_dir_generator(char dir[])
{
	int root_size=strlen(root);
	int dir_size=strlen(dir);
	int i;

	relative_curr_dir[0]='~';
	if(root_size<dir_size)
	{
		for(i=0;i<root_size;i++)
		{
			if(root[i]!=dir[i])
			{
				break;
			}
		}
		if(i==root_size)
		{
			for(;dir[i]!='\0';i++)
			{
				relative_curr_dir[i-root_size+1]=dir[i];
			}
			relative_curr_dir[i-root_size+1]='\0';

			return;
		}
	}
	else if(root_size==dir_size)
	{
		for(i=0;i<root_size;i++)
		{
			if(root[i]!=dir[i])
			{
				break;
			}
		}
		if(i==root_size)
		{
			relative_curr_dir[1]='\0';
		}

		return;
	}

	for(i=0;dir[i]!='\0';i++)
	{
		relative_curr_dir[i]=dir[i];
	}
	relative_curr_dir[i]='\0';

	return;

}