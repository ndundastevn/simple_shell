#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stddef.h>

#define MAX_INPUT 1024
#define MAX_ALIAS_NAME 100
#define MAX_ALIAS_VALUE 100

/* function prototypes */

struct alias
{
	char name[MAX_ALIAS_NAME];
	char value[MAX_ALIAS_VALUE];
};

struct alias aliases[100];
int num_aliases;

int main(void);
int atoi(const char *str);
int command_line(char **argv);
void print_error(char *command);
int execute_command(char **args);
void exit_shell(void);
char *read_command(void);
char **parse_command(char *command);
void print_env(void);
int get_env(void);
char *custom_getline(void);
int main_exit(void);
void execute(char **argv);
char **parse_line(char *line);
char *read_line(void);
void unset_env(char **argv);
void set_env(char **argv);
int builtin_cd(char **argv, char **oldpwd);
int change_directory(const char *path, char **oldpwd);
int execute_command_sep(char *cmd);
int main_sep(void);
int handle_logical_operators(char **args, int command_result);
void print_aliases(void);
void print_aliases_for_names(char **args);
void define_aliases(char **args);
void alias_command(char **args);
int main_var(void);
int get_variable_name_length(char *var_start, char **var_end);
char *get_variable_value(char *var_name);
void replace_variables(char *command);
void replace_variable(char *var_start, char *var_end,
		char *var_name, char *var_value, char *command);
char **get_args(char *str);
int main_filename(int ac, char **av);

#endif /* SHELL_H */
