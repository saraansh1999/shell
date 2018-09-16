#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include "../definitions.h"
#define buffer_size 1000000

typedef struct files
{
	int pid;
	long long int time;
	char state[50];
	char name[1005];
	char no[50];
}files;

int compare(const void *a,const void *b)
{
	const files* q=(files*)a;
	const files* w=(files*)b;
	if(q->time-w->time>0)
		return 1;
	if(q->time-w->time==0)
		return 0;
	if(q->time-w->time<0)
		return -1;
}

void jobs_command_execute()
{
	files jobs[1005];
	int i,j,c=0,z,f;
	char buffer[buffer_size],temp[50],status_filename[1005],time_filename[1005];
	DIR *dir;
	FILE *file;
	struct dirent *sub;

	strcpy(status_filename,"/proc/");
	strcpy(time_filename,"/proc/");

	if((dir=opendir(status_filename))==NULL)
	{
		printf("ERROR : Cannot access proc files.\n");
		exit(EXIT_FAILURE);
	}
	while((sub=readdir(dir))!=NULL)
	{
		strcpy(status_filename,"/proc/");
		strcpy(time_filename,"/proc/");
		f=0;
		for(i=0;sub->d_name[i]!='\0';i++)
		{
			if((sub->d_name[i]-'0')>=0 && (sub->d_name[i]-'0')<=9)
				continue;
			else
				f++;
		}
		if(f==0)
		{
			strcat(status_filename,sub->d_name);
			strcat(time_filename,sub->d_name);
			strcat(status_filename,"/status");
			strcat(time_filename,"/stat");
			status_filename[13+strlen(sub->d_name)]='\0';
			time_filename[11+strlen(sub->d_name)]='\0';

			if((file=fopen(status_filename,"r"))!=NULL)
			{
				while(fgets(buffer,buffer_size,file)!=NULL)
				{
					if(strncmp(buffer,"Name",4)==0)
					{
						for(j=5;buffer[j]!='\n';j++)
							if(isspace(buffer[j]))
								continue;
							else
								break;
						z=0;
						for(;buffer[j]!='\n';j++)
							jobs[c].name[z++]=buffer[j];
						jobs[c].name[z]='\0';

					}
					else if(strncmp(buffer,"State",5)==0)
					{
						for(j=5;buffer[j]!='\n';j++)
							if(isspace(buffer[j]))
								continue;
							else
								break;
						z=0;
						for(;buffer[j]!='\n';j++)
							jobs[c].state[z++]=buffer[j];
						jobs[c].state[z]='\0';

					}
					if(strncmp(buffer,"Pid",3)==0)
					{
						for(j=5;buffer[j]!='\n';j++)
							if(isspace(buffer[j]))
								continue;
							else
								break;
						z=0;
						for(;buffer[j]!='\n';j++)
							jobs[c].no[z++]=buffer[j];
						jobs[c].no[z]='\0';
						sscanf(jobs[c].no,"%d",&jobs[c].pid);
					}
				}
					fclose(file);
			}
			else
			{
				printf("ERROR : Information file not found.\n");
				exit(EXIT_FAILURE);
			}

			if((file=fopen(time_filename,"r"))!=NULL)
			{
				for(j=1;j<=21;j++)
					fscanf(file,"%s",temp);
				fscanf(file,"%lld",&jobs[c].time);
				fclose(file);
			}
			else
			{
				printf("ERROR : Information file not found.\n");
				exit(EXIT_FAILURE);	
			}
			c++;
		}
	}
	qsort(jobs,c,sizeof(files),compare);
	for(i=0;i<c;i++)
	{
		printf("[%d]     %s     %s [%d]\n",i+1,jobs[i].state,jobs[i].name,jobs[i].pid );
	}
	exit(EXIT_SUCCESS);
}