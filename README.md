# Readline (library)
This project aim to recreate the C readline library, it main functions and functionality<br>
In the original library, `readline()` leaks a lot, so I decided to redo it WITHOUT any leaks
```
char  *readline(char *prompt, int ret);
void	add_history(char *line);
void	clear_history(void);
```
*readline()* takes two arguments, a string (prompt) and an int (ret). Both are use to make the prompt: ret to **take** account a value (return value for example), and **prompt** to write watever you want as prompt<br>
*add_history()* take one argument and it add the line to the history file (.rdlrc/history)<br>
*clear_history()* reset the history file (.rdlrc/history)
#### Functionality
* **auto-completion and Tab** [shows the different results or changes the word if there is only one possibility]
* **history with directional keys** (up and down) [the history is preserved even if you quit the programm thanks to history file *.rdlrc/,history*]
#### Man
* `make` &nbsp;&nbsp; --> &nbsp;&nbsp;compile a library "*libreadline.a*"
* `make test` &nbsp;&nbsp; --> &nbsp;&nbsp;compile the C file test.c to test the function into "*test*"
* `make clean` &nbsp;&nbsp; --> &nbsp;&nbsp;delete .o files
* `make fclean` &nbsp;&nbsp; --> &nbsp;&nbsp;delete .o files, the library and test
* `make dclean` &nbsp;&nbsp; --> &nbsp;&nbsp;delete the directory *.rdlrc/*

<br>If you want to link this library, just include the header file and link the static library
##### 1. Include the header
```
# include "./readline/readline.h"
```
##### 2. transform c file into object file
```
${GCC} ${FLAGS} file.c -c
```
##### 3. link the library
```
${GCC} ${FLAGS} *.o -L. -lreadline
```
<br><br>Date: 27 Jul 2023
