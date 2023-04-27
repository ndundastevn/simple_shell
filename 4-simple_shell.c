#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "shell.h"
extern char **environ;

void print_error(char *command);
int execute_command(char **args);
void exit_shell(void);
/**
 * execute_command - Executes a command.
 * @args: An array of argument strings.
 *
 * Description: This function implements the exit built-in command
 *              that exits the shell with a status code of 0.
 *
 * Return: Always returns 0.
 */
int execute_command(char **args)
{
    pid_t pid;
    int status;
    int ret;

    pid = fork();
    if (pid == 0) {
        ret = execve(args[0], args, environ);
        if (ret == -1) {
            print_error(args[0]);
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        perror("shell");
    } else {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}


/**
 * exit_shell - exit shell and prints 'success'
 *
 * Return: Always 0.
 */
void exit_shell(void)
{
	printf("Goodbye!\n");
	exit(0);
}

void print_error(char *command)
{
    char *error_message = strerror(errno);
    fprintf(stderr, "%s: %s: %s\n", "shell", command, error_message);
}
