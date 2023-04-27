#include "myshell.h"
/**
 * hsh - the main loop for the shell program
 * @info: a pointer to the info_t struct
 * @av: a pointer to an array of strings
 *
 * Return: the exit status of the program or -1 on failure
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (_interactive(info))
			_eputsft("$ ");
		_eputcharr(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_inbuilt(info);
			if (builtin_ret == -1)
				find_inbuilt(info);
		}
		else if (_interactive(info))
			_eputcharr('\n');
		free_info(info, 0);
	}
	write_histo(info);
	free_info(info, 1);
	if (!_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_inbuilt - find a builtin command in the command table
 * @info: a pointer to the info_t struct
 *
 * Return: the exit status of the builtin command or -1 if not found
 */
int find_inbuilt(info_t *info)
{
	int i, built_in_ret = -1;
	inbuilt_table builtintbl[] = {
		{"exit", _cdexit},
		{"env", _cdenv},
		{"help", _cdhelp},
		{"history", _cdhisto},
		{"setenv", _cdsetenv},
		{"unsetenv", _cdunsetenv},
		{"cd", _cdcd},
		{"alias", _cdalias},
		{NULL, NULL}
	};
	

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - find a command in the path and execute it
 * @info: a pointer to the info_t struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((_interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_command - create a child process and execute the command
 * @info: a pointer to the info_t struct
 *
 * Return: void
 */
void fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
