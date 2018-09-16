# Shell in C
> This is a functional shell coded in C language.

### Execution
> Run the following commands : 
> <br>```make ```<br>
> ```./shell ```

### Features
* Modular code
* Shell works with the directory from where it was executed as '~'.
* Background and foreground processes supported.
* Shell supports I/O redirection.
* Shell supports piping of commands.
* Shell supports ```Ctrl+Z``` to stop a currently running foreground job.
* Shell supports ```Ctrl+C``` to terminate a currently running foreground job.
* ';' separated commands supported.
* The commands ```ls``` ```echo``` ```pwd``` ```pinfo``` ```clock``` ```remindme``` ```cd``` ```setenv``` ```unsetenv``` ```jobs``` ```kjob``` ```fg``` ```bg``` ```overkill``` are in-built in the shell.
* Command ```jobs``` lists out all the currently running processes that are recorded by '/proc'.
* Command ```kjob <jobNumber> <signalNumber>``` can be used to send a signal to a job.
* Command ```fg <jobNumber>``` can be used to bring a job to foreground.
* Command ```bg <jobNumber>``` can be used to start a stopped job in the background.
* Command ```overkill``` can be used to kill all background jobs at once.
* Command ```setenv``` can be used to initialize and update environment variables.
* Command ```unsetenv``` can be used to delete environment variables.
* Command ```clock -t x``` supported where x is the interval after which time will be printed on screen.(Can be terminated with Ctrl+C)
* Command ```remindme message t``` which would remind the user with 'message' after time t.
* Command ```pinfo <id>``` supported which prints out the process information of the process with pid 'id'
* Command ```echo``` can be used with double qoutes to preserve whitespaces.Moreover '\n', '\\' and '\"' are supprted too with echo.
* All the other basic shell commands are supported as they are.

### Exit
> ```quit```
