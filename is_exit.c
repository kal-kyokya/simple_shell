#include "shell.h"

/**
 * is_exit - Checks if input string is "exit". 
 * @argv: List of cmd line arguments.
 * @input: String input from stdin.
 *
 * Return: Nothing.
 */
void is_exit(char **argv, char *input)
{
	int count;

	if (argv == NULL || argv[0] == NULL || *arg[0] == '\0')
		return;
	count = 0;
	while (argv[count] != NULL)
	{
		if (strcmp(argv[count], "exit") == 0)
		{
			free(input);
			free(argv);
			exit (0);
		}
		count++;
	}
}
