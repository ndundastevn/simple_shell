#ifndef _SHELL_H_
#define _SHELL_H_

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
extern char **environ;
/* Global variables */
extern char **environ;

/* function prototypes */
int main(void);
void print_prompt(void);
void print_error(char *command, int count);
char *read_input(void);
char **split_input(char *input);
int execute_command(char **args);
char *get_path(char *command);


#endif /* _SHELL_H_ */

