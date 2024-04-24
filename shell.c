#include "shell.h"

/**
 * main - unix command line interpreter
 *
 * Return: void.
 */

int main(void)
{
	ssize_t read;
	char *input = NULL, **argv = NULL;
	size_t len = 0;
	pid_t pid;

	while (1)
	{
		display_prompt();
		read = getline(&input, &len, stdin);
		if (read > 1 && is_all_spaces(input, read))
			continue;
		if (read > 1)
		{
			input[read - 1] = '\0';
			argv = tokenize(input);
			is_exit(argv, input);
			is_env(argv);
			argv[0] = get_path(argv);
			if (argv[0] == NULL)
			{
				perror("Error: ");
				continue;
			}
			pid = fork();
			if (pid == -1)
				exit(-1);
			else if (pid == 0)
				exec_ve(argv);
			else
				wait(NULL);
			free(argv[0]);
			free(argv);
		}
		else if (read == -1 || read == 0)
			break;
	}
	free(input);
	return (0);
}
