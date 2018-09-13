shell : \
			main.o \
			put_prompt.o \
			get_command.o \
			break_up_command.o \
			command_execute.o \
			redirections.o \
			cd_command_execute.o \
			ls_command_execute.o \
			pwd_command_execute.o \
			echo_command_execute.o \
			pinfo_command_execute.o \
			remindme_command_execute.o \
			clock_command_execute.o \
			system_command_execute.o \
			relative_curr_dir_generator.o \
			signals.o \
			check_bg_exit.o 
		$(CC) -g -o shell $^


main.o : definitions.h main.c
		$(CC) -g -c main.c


put_prompt.o : definitions.h functions/put_prompt.c
		$(CC) -g -c functions/put_prompt.c


get_command.o : definitions.h functions/get_command.c
		$(CC) -g -c functions/get_command.c


break_up_command.o : definitions.h functions/break_up_command.c
		$(CC) -g -c functions/break_up_command.c


command_execute.o : definitions.h functions/command_execute.c
		$(CC) -g -c functions/command_execute.c

redirections.o : definitions.h functions/redirections.c
		$(CC) -g -c functions/redirections.c

cd_command_execute.o : definitions.h functions/cd_command_execute.c
		$(CC) -g -c functions/cd_command_execute.c


ls_command_execute.o : definitions.h functions/ls_command_execute.c
		$(CC) -g -c functions/ls_command_execute.c


pwd_command_execute.o : definitions.h functions/pwd_command_execute.c
		$(CC) -g -c functions/pwd_command_execute.c


echo_command_execute.o : definitions.h functions/echo_command_execute.c
		$(CC) -g -c functions/echo_command_execute.c


pinfo_command_execute.o : definitions.h functions/pinfo_command_execute.c
		$(CC) -g -c functions/pinfo_command_execute.c


remindme_command_execute.o : definitions.h functions/remindme_command_execute.c
		$(CC) -g -c functions/remindme_command_execute.c


clock_command_execute.o : definitions.h functions/clock_command_execute.c
		$(CC) -g -c functions/clock_command_execute.c


system_command_execute.o : definitions.h functions/system_command_execute.c
		$(CC) -g -c functions/system_command_execute.c


relative_curr_dir_generator.o : definitions.h functions/relative_curr_dir_generator.c
		$(CC) -g -c functions/relative_curr_dir_generator.c


check_bg_exit.o : definitions.h functions/check_bg_exit.c
		$(CC) -g -c functions/check_bg_exit.c


signals.o : functions/signals.c
		$(CC) -g -c functions/signals.c


clean : 
		rm -f shell *.o