#include "shell.h"

/**
 * main - unix command line interpreter
 *
 * Return: void.
 */

int main(void)
{
	char *input = NULL;
	size_t len = 0;
	ssize_t read;
	char *argv[2];
	pid_t pid;

	while (1)
	{
		printf("($) ");
		read = getline(&input, &len, stdin);
		if (read != -1)
		{
			input[read - 1] = '\0';
			argv[0] = input;
			argv[1] = NULL;
			pid = fork();
			if (pid == -1)
				printf("error\n");

			if (pid == 0)
			{
				if ((execve(argv[0], argv, NULL) == -1))
					printf("error\n");
			}
			else
				wait(NULL);
		}

		else
			printf("error\n");

	}
	free(input);

	return (0);
}
