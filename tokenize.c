#include "shell.h"

/**
 * tokenize - tokenizes the input
 * @input: string read from stdin
 *
 * Return: array of argumrnts.
 */

char **tokenize(char *input)
{
	const char delim[] = " ";
	char *token;
	int  i = 0;
	char **argv = NULL;

	argv = (char **)malloc(sizeof(char *) * (strlen(input) + 1));
	if (argv == NULL)
		return (NULL);
	token = strtok(input, delim);
	while (token != NULL)
	{
		argv[i] = token;
		token = strtok(NULL, delim);
		i++;
	}
	argv[i] = NULL;

	return (argv);
}
