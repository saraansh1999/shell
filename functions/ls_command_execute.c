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


void ls_command_execute(char** args,int size)
{
	int flag_l=0,flag_a=0,i=1,file_count=0,n,j,ret,f=0;
	char** files=(char**)malloc(size*sizeof(char*));
	char curr_dir[1005],path[1005];
	struct dirent **this_file;
	struct stat info,pre_info;
	getcwd(curr_dir,1000);
	

	while(args[i]!=NULL)
	{
		if(strcmp(args[i],"-l")==0)
			flag_l=1;
		else if(strcmp(args[i],"-a")==0)
			flag_a=1;
		else if(strcmp(args[i],"-la")==0 || strcmp(args[i],"-al")==0)
		{
			flag_l=1;
			flag_a=1;
		}
		else
		{
			files[file_count]=(char*)malloc(1005*sizeof(char));
			strcpy(files[file_count++],args[i]);
		}
		i++;
	}
	/*while(i<file_count)
	{
		printf("%s\n",files[i]);
		i++;
	}
	printf("%d %d\n",flag_l,flag_a );*/

	if(file_count==0)
	{
		files[file_count]=(char*)malloc(1005*sizeof(char));
		strcpy(files[file_count++],curr_dir);
		f++;
	}

	i=0;
	while(i<file_count)
	{
		ret=stat(files[i],&pre_info);
		if(ret==-1)
		{
			fprintf(stderr,"ERROR : Cannot get info about file %s\n",files[i]);
			exit(EXIT_FAILURE);
		}
		if(S_ISDIR(pre_info.st_mode))
		{
			n=scandir(files[i],&this_file,NULL,alphasort);
			if(n==-1)
			{
				fprintf(stderr,"ERROR : Cannot scan directory %s\n",files[i]);
				exit(EXIT_FAILURE);
			}
			j=0;

			while(j<n)
			{
				strcpy(path,curr_dir);
				strcat(path,"/");
				if(f==0)
				{
					strcat(path,files[i]);
					strcat(path,"/");
				}
				strcat(path,this_file[j]->d_name);
				ret=stat(path,&info);
				if(ret==-1)
				{
					fprintf(stderr,"ERROR : Cannot get info about file %s %s\n",path,this_file[j]->d_name);
					exit(EXIT_FAILURE);
				}
				if(this_file[j]->d_name[0]=='.' && flag_a==0)
				{}
				else
				{
					if(flag_l==1)
					{
						printf((S_ISDIR(info.st_mode)?"d":"-"));
						printf((info.st_mode&S_IRUSR)?"r":"-");
						printf((info.st_mode&S_IWUSR)?"w":"-");
						printf((info.st_mode&S_IXUSR)?"x":"-");
						printf((info.st_mode&S_IRGRP)?"r":"-");
						printf((info.st_mode&S_IWGRP)?"w":"-");
						printf((info.st_mode&S_IXGRP)?"x":"-");
						printf((info.st_mode&S_IROTH)?"r":"-");
						printf((info.st_mode&S_IWOTH)?"w":"-");
						printf((info.st_mode&S_IXOTH)?"x":"-");
						printf(" ");
						printf("%lu ",info.st_nlink);
						struct passwd *pwd=getpwuid(info.st_uid);
						if(pwd)
						{
							printf("%s ",pwd->pw_name );
						}
						else
						{
							fprintf(stderr,"ERROR : User not found\n");
							exit(EXIT_FAILURE);
						}
						struct group *grp=getgrgid(info.st_gid);
						if(grp)
						{
							printf("%s ",grp->gr_name );
						}
						else
						{
							fprintf(stderr,"ERROR : Group not found\n");
							exit(EXIT_FAILURE);
						}
						printf("%ld ",info.st_size);
						struct timespec last_modify=info.st_mtim;
						char time[100];
						strcpy(time,ctime(&last_modify.tv_sec));
						time[strlen(time)-1]='\0';
						printf("%s ",time);
					}
					printf("%s\n",this_file[j]->d_name);
				}
				free(this_file[j]);
				j++;
			}
			free(this_file);
		}
		else
		{
			ret=stat(files[i],&info);
			if(ret==-1)
			{
				fprintf(stderr,"ERROR : Cannot get info about file %s\n",files[i]);
				exit(EXIT_FAILURE);
			}
			if(files[i][0]=='.' && flag_a==0)
			{}
			else
			{
				if(flag_l==1)
				{
					printf((S_ISDIR(info.st_mode)?"d":"-"));
					printf((info.st_mode&S_IRUSR)?"r":"-");
					printf((info.st_mode&S_IWUSR)?"w":"-");
					printf((info.st_mode&S_IXUSR)?"x":"-");
					printf((info.st_mode&S_IRGRP)?"r":"-");
					printf((info.st_mode&S_IWGRP)?"w":"-");
					printf((info.st_mode&S_IXGRP)?"x":"-");
					printf((info.st_mode&S_IROTH)?"r":"-");
					printf((info.st_mode&S_IWOTH)?"w":"-");
					printf((info.st_mode&S_IXOTH)?"x":"-");
					printf(" ");
					printf("%lu ",info.st_nlink);
					struct passwd *pwd=getpwuid(info.st_uid);
					if(pwd)
					{
						printf("%s ",pwd->pw_name );
					}
					else
					{
						fprintf(stderr,"ERROR : User not found\n");
						exit(EXIT_FAILURE);
					}
					struct group *grp=getgrgid(info.st_gid);
					if(grp)
					{
						printf("%s ",grp->gr_name );
					}
					else
					{
						fprintf(stderr,"ERROR : Group not found\n");
						exit(EXIT_FAILURE);
					}
					printf("%ld ",info.st_size);
					struct timespec last_modify=info.st_mtim;
					char time[100];
					strcpy(time,ctime(&last_modify.tv_sec));
					time[strlen(time)-1]='\0';
					printf("%s ",time);
				}
				printf("%s\n",files[i]);
			}
		}
		i++;
	}


	i=0;
	for(;i<file_count;i++)
		free(files[i]);
	free(files);

	exit(EXIT_SUCCESS);

}