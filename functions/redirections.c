#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include "../definitions.h"


int stdout_clone_for_red,stdout_clone_for_pipe;
int stdin_clone_for_red,stdin_clone_for_pipe;


int redirect_to_file(char comm[],int out_red,int last_letter,int size)
{
	int fd,i=last_letter,c=0;
	if(out_red)
	{
		char* file_name=(char*)malloc((size+5)*sizeof(char));
		for(;comm[i]!='\0';i++)
		{
			if(comm[i]==' ' || comm[i]=='\t' || comm[i]=='\v' || comm[i]=='\r' || comm[i]=='\n' || comm[i]=='\f' || comm[i]=='\a')
				continue;
			else
				break;
		}
		for(;comm[i]!='\0' && !(comm[i]==' ' || comm[i]=='\t' || comm[i]=='\v' || comm[i]=='\r' || comm[i]=='\n' || comm[i]=='\f' || comm[i]=='\a');i++)
		{
			file_name[c++]=comm[i];
			comm[i]=' ';
		}

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

		/*if(dup2(1,stdout_clone_for_red)==-1)
		{
			printf("ERROR : Redirection Failed.\n");
			return 1;	
		}*/
		stdout_clone_for_red=dup(1);
		if(stdout_clone_for_red==-1)
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

int redirect_from_file(char comm[],int last_letter,int size)
{
	int c=0,i,fd;
	char* file_name=(char*)malloc((size+5)*sizeof(char));
	i=last_letter;
	for(;comm[i]!='\0';i++)
	{
		if(comm[i]==' ' || comm[i]=='\t' || comm[i]=='\v' || comm[i]=='\r' || comm[i]=='\n' || comm[i]=='\f' || comm[i]=='\a')
			continue;
		else
			break;
	}
	for(;comm[i]!='\0' && !(comm[i]==' ' || comm[i]=='\t' || comm[i]=='\v' || comm[i]=='\r' || comm[i]=='\n' || comm[i]=='\f' || comm[i]=='\a');i++)
	{
		file_name[c++]=comm[i];
		comm[i]=' ';
	}

	file_name[c]='\0';

	fd=open(file_name, O_RDONLY);

	if(fd==-1)
	{
		printf("ERROR : File not found.\n");
		return 1;
	}

/*	if(dup2(0,stdin_clone_for_red)==-1)
	{
		printf("ERROR : Redirection Failed.\n");
		return 1;
	}*/
	stdin_clone_for_red=dup(0);
	if(stdin_clone_for_red==-1)
	{
		printf("ERROR : Redirection Failed.\n");
		return 1;
	}

	close(0);

	if(dup2(fd,0)==-1)
	{
		printf("ERROR : Redirection Failed.\n");
		return 1;
	}

	close(fd);

	return 0;

}

int send_to_pipe(int *fd)
{
	stdout_clone_for_pipe=dup(1);
	if(stdout_clone_for_pipe==-1)
	{
		printf("ERROR : Redirection Failed\n");
		return 1;
	}

	if(dup2(*fd,1)==-1)
	{
		printf("ERROR : Redirection Failed\n");
		return 1;
	}

	close(*fd);

	return 0;
}

int receive_from_pipe(int *fd)
{
	stdin_clone_for_pipe=dup(0);
	if(stdin_clone_for_pipe==-1)
	{
		printf("ERROR : Redirection Failed\n");
		return 1;
	}	

	if(dup2(*fd,0)==-1)
	{
		printf("ERROR : Redirection Failed\n");
		return 1;	
	}

	close(*fd);

	return 0;
}

int close_pipe_out()
{
	if(dup2(stdout_clone_for_pipe,1)==-1)
	{
		printf("ERROR : Redirection Failed.\n");
		return 1;
	}
	return 0;
}

int close_pipe_in()
{
	if(dup2(stdin_clone_for_pipe,0)==-1)
	{
		printf("ERROR : Redirection Failed.\n");
		return 1;
	}
	return 0;
}

int close_redirection_out()
{
	if(dup2(stdout_clone_for_red,1)==-1)
	{
		printf("ERROR : Redirection Failed.\n");
		return 1;
	}
	return 0;
}

int close_redirection_in()
{
	if(dup2(stdin_clone_for_red,0)==-1)
	{
		printf("ERROR : Redirection Failed.\n");
		return 1;
	}
	return 0;
}