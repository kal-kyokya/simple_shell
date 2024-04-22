#include "shell.h"

/**
 * is_env - Checks if 'env' command is run.
 * @argv: List of cmd line arguments.
 *
 * Return: Nothing.
 */
void is_env(char **argv)
{
	char **env;
	int count;

	env = environ;
	count = 0;
	if (argv == NULL || argv[0] == NULL || *argv[0] == '\0')
		return;
	if (strcmp(argv[0], "env") == 0)
	{
		while (env[count])
			printf("%s\n", env[count++]);
	}
}
