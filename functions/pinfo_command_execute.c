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


void pinfo_command_execute(char** args,int id)
{
	FILE* file;
	int no;
	char path[1005];
	char data[3003];
	char current[100];
	
	strcpy(path,"/proc/");
	
	if(args[1]==NULL)
	{
		sprintf(current,"%d",shell_id);
		strcat(path,current);
	}
	else
		strcat(path,args[1]);

	strcat(path,"/status");


	file=fopen(path,"r");
	if(file==NULL)
	{
		fprintf(stderr,"ERROR : File %s can't be opened.\n",path);
		if(id==0)
			exit(EXIT_FAILURE);
		else
			return ;
	}
	while(fgets(data,3003,file)!=NULL)
	{
		if(data[0]=='S' && data[1]=='t' && data[2]=='a' && data[3]=='t' && data[4]=='e')
			printf("%s",data );
		else if(data[0]=='V' && data[1]=='m' && data[2]=='S' && data[3]=='i' && data[4]=='z' && data[5]=='e')
			printf("%s",data );
		else if(data[0]=='P' && data[1]=='i' && data[2]=='d')
			printf("%s",data );
	}
	fclose(file);

	strcpy(path,"/proc/");
	
	if(args[1]==NULL)
	{
		strcat(path,current);
	}
	else
	{
		strcat(path,args[1]);
	}

	strcat(path,"/exe");
	
	no=readlink(path,data,1005);
	if(no==-1)
	{
		fprintf(stderr,"ERROR : Cannot resolve executable path.\n");
		if(id==0)
			exit(EXIT_FAILURE);
		else
			return ;
	}
	data[no]='\0';
	printf("Executable Path: %s\n",data );
		
	if(id==0)
		exit(EXIT_SUCCESS);
	else
		return ;
}