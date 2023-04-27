#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"


/**
 * print_aliases - Prints all the aliases in the aliases array
 *
 * Return: void
 */
void print_aliases(void)
{
	int i;

	for (i = 0; i < num_aliases; i++)
	{
		printf("%s='%s'\n", aliases[i].name, aliases[i].value);
	}
}

/**
 * print_aliases_for_names - Prints aliases for the given names
 * @args: A double pointer to an array of strings
 *
 * Return: void
 */
void print_aliases_for_names(char **args)
{
	int i, j;

	for (i = 1; args[i] != NULL; i++)
	{
		for (j = 0; j < num_aliases; j++)
		{
			if (strcmp(args[i], aliases[j].name) == 0)
			{
				printf("%s='%s'\n", aliases[j].name, aliases[j].value);
				break;
			}
		}
	}
}

/**
 * define_aliases - Updates or adds an alias in the aliases array
 * @args: Array of strings containing the command line arguments
 *
 * Return: Always 0
 */
void define_aliases(char **args)
{
	int i, j;

	for (i = 1; args[i] != NULL; i++)
	{
		for (j = 0; j < num_aliases; j++)
		{
			if (strcmp(args[i], aliases[j].name) == 0)
			{
				strncpy(aliases[j].value, args[i + 1], MAX_ALIAS_VALUE - 1);
					break;
			}
		}
		if (j == num_aliases)
		{
			strncpy(aliases[num_aliases].name, args[i], MAX_ALIAS_NAME - 1);
			strncpy(aliases[num_aliases].value, args[i + 1], MAX_ALIAS_VALUE - 1);
			num_aliases++;
		}
		i++;
	}
}

/**
 * main_elias - entry point for alias program
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: always 0
 */
int main_elias(int argc, char **argv)
{
	if (argc == 1)
	{
		print_aliases();
	}
	else
	{
		if (strcmp(argv[1], "-p") == 0)
		{
			print_aliases_for_names(argv);
		}
		else
		{
			define_aliases(argv);
		}
	}
	return (0);
}
