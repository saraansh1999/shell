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

void trim(char* arr)
{
	int len=strlen(arr);
	char* temp_beg=arr;
	char* temp_end=arr+len-1;

	while(temp_beg<=temp_end && isspace(temp_end[0]))
	{
		len--;
		temp_end--;
	}

	while(temp_beg<=temp_end && isspace(temp_beg[0]))
	{
		len--;
		temp_beg++;
	}

	memmove(arr,temp_beg,len);
	arr[len]='\0';

}


void break_up_command(char* comm,int no_commands,int size)
{
	char** array_of_commands,**piped_elements;
	char* ptr,*ptr2;
	char* command=(char*)malloc(size*sizeof(char));
	int i=0,j,prev,next;
	int bg;
	strcpy(command,comm);
	array_of_commands=(char**)malloc((no_commands+5)*sizeof(char*));
	piped_elements=(char**)malloc((size)*sizeof(char*));
	
	array_of_commands[0]=strtok_r(command,";",&ptr);
	while(array_of_commands[i]!=NULL)
	{
		j=0;

		trim(array_of_commands[i]);
		
		piped_elements[0]=strtok_r(array_of_commands[i],"|",&ptr2);
		while(piped_elements[j]!=NULL)
		{
			prev=0;
			next=0;
			trim(piped_elements[j]);
			
			if(piped_elements[i][strlen(piped_elements[i])-1]=='&')
				bg=1;
			else
				bg=0;
			
			if(j>0)
				prev=1;

			j++;
			piped_elements[j]=strtok_r(NULL,"|",&ptr2);
			
			if(piped_elements[j]!=NULL)
				next=1;
			
			command_execute(piped_elements[j-1],bg,strlen(piped_elements[j-1]),prev,next);

		}
		
		
		i++;
		array_of_commands[i]=strtok_r(NULL,";",&ptr);
	}
	//printf("br exit\n");
	free(command);
	//printf("freed\n");
	free(array_of_commands);
	//printf("freed\n");
	return;	
}