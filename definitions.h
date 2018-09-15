#ifndef DEFIN
#define DEFIN


typedef struct bg_processes{
	int pid;
	char name[1005];
}bg_processes;


int close_shell;
char root[1005];
char relative_curr_dir[1005];
char delim[10];
int shell_id;
bg_processes bgpro[1005];


void global_signal_handler(int sig);

void clock_signal_handler(int sig);

void relative_curr_dir_generator(char dir[]);

void put_prompt();

void system_command_execute(char** args,int red);

void cd_command_execute(char** args,int pid);

void ls_command_execute(char** args,int size);

void pwd_command_execute(char** args);

void pinfo_command_execute(char** args,int id);

void echo_command_execute(char* command);

void remindme_command_execute(char** args);

void clock_command_execute(char ** args);

int redirect_to_file(char comm[],int out_red,int last_letter,int size);

int close_redirection_out();

int redirect_from_file(char comm[],int last_letter,int size);

int close_redirection_in();

void command_execute(char* comm,int bg,int size);

void break_up_command(char* comm,int no_commands,int size);

void get_command();

void check_bg_exit();


#endif
