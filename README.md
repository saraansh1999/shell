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
* ';' separated commands supported.
* The commands ```ls``` ```echo``` ```pwd``` ```pinfo``` ```clock``` ```remindme``` ```cd``` ```setenv``` ```unsetenv``` ```jobs``` are in-built in the shell.
* Command ```jobs``` lists out all the currently running processes that are recorded by '/proc'.
* Command ```setenv``` can be used to initialize and update environment variables.
* Command ```unsetenv``` can be used to delete environment variables.
* Command ```clock -t x``` supported where x is the interval after which time will be printed on screen.(Can be terminated with Ctrl+C)
* Command ```remindme message t``` which would remind the user with 'message' after time t.
* Command ```pinfo <id>``` supported which prints out the process information of the process with pid 'id'
* Command ```echo``` can be used with double qoutes to preserve whitespaces.Moreover '\n', '\\' and '\"' are supprted too with echo.
* All the other basic shell commands are supported as they are.

### Exit
> ```exit``` or Ctrl+Z
