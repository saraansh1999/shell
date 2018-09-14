#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include "../definitions.h"


int stdout_clone;


int redirect_to_file(char comm[],int out_red,int last_letter,int size)
{
	int fd,i,c=0;
	if(out_red)
	{
		char* file_name=(char*)malloc((size+5)*sizeof(char));
		if(out_red==1)
			i=last_letter+1;
		else
			i=last_letter+2;
		for(;comm[i]!='\0';i++)
		{
			if(comm[i]==' ' || comm[i]=='\t' || comm[i]=='\v' || comm[i]=='\r' || comm[i]=='\n' || comm[i]=='\f' || comm[i]=='\a')
				continue;
			else
				break;
		}
		for(;comm[i]!='\0';i++)
			file_name[c++]=comm[i];

		file_name[c]='\0';

		if(out_red==1)
		{
			fd=open(file_name,O_WRONLY | O_CREAT | O_TRUNC , 0644);
		}
		else
			fd=open(file_name,O_WRONLY | O_CREAT | O_APPEND , 0644);

		if(fd==-1)
		{
			printf("ERROR :File not found.\n");
			return 1;
		}

		if(dup2(1,stdout_clone)==-1)
		{
			printf("ERROR : Redirection Failed.\n");
			return 1;	
		}

		close(1);

		if(dup2(fd,1)==-1)
		{
			printf("ERROR : Redirection Failed.\n");
			return 1;
		}

		close(fd);
	}

	return 0;
}

int close_redirection()
{
	if(dup2(stdout_clone,1)==-1)
	{
		printf("ERROR : Redirection Failed.\n");
		return 1;
	}
	return 0;
}