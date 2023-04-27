#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>


#define BUFFER_SIZE 1024

extern char **environ;

char *read_line(void)
{
    static char buffer[BUFFER_SIZE];
    static int pos = 0;
    int c;

    while (1) {
        c = getchar();
        if (c == EOF || c == '\n') {
            buffer[pos] = '\0';
            pos = 0;
            return strdup(buffer);
        } else {
            buffer[pos] = c;
            pos++;
        }
        if (pos >= BUFFER_SIZE) {
            printf("Input too long\n");
            pos = 0;
            return NULL;
        }
    }
}

void print_error(char *command)
{
    char *message = malloc(sizeof(char) * (strlen(command) + 21));
    strcpy(message, "shell: ");
    strcat(message, command);
    perror(message);
    free(message);
}

void execute_command(char *command)
{
    char **argv = malloc(sizeof(char *) * BUFFER_SIZE);
    int argc = 0;

    char *token = strtok(command, " ");
    while (token != NULL && argc < BUFFER_SIZE) {
        argv[argc] = token;
        argc++;
        token = strtok(NULL, " ");
    }
    argv[argc] = NULL;

    if (strcmp(argv[0], "exit") == 0) {
        exit(0);
    } else if (strcmp(argv[0], "cd") == 0) {
        if (argc == 2) {
            if (chdir(argv[1]) == -1) {
                print_error(argv[1]);
            }
        } else {
            printf("cd: invalid arguments\n");
        }
    } else if (strcmp(argv[0], "env") == 0) {
        int i = 0;
        while (environ[i] != NULL) {
            printf("%s\n", environ[i]);
            i++;
        }
    } else {
        if (fork() == 0) {
            if (execvp(argv[0], argv) == -1) {
                print_error(argv[0]);
                exit(1);
            }
        } else {
            wait(NULL);
        }
    }
    free(argv);
}

int main(void)
{
    char *line;

    while (1) {
        printf("shell-0.1$ ");
        line = read_line();
        if (line[0] != '\0') {
            execute_command(line);
        }
        free(line);
    }

    return 0;
}

