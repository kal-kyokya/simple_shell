#include "shell.h"

/**
 * exec_ve - executes the command.
 * @argv: array of arguments.
 *
 * Return: Nothing.
 */
void exec_ve(char **argv)
{
	if ((execve(argv[0], argv, NULL) == -1))
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}
