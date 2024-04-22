#include "main.h"

#define BUFFER_SIZE 1024

char **tokenize(char *buffer);

/**
 * main - Entry point to the function.
 *
 * Return: 0 if program runs successfully.
 */
int main(void)
{
	char *getline_buff = NULL, buffer[BUFFER_SIZE], **env = environ, **arg;
	pid_t my_pid;
	size_t getline_len = 0;
	int count = 0, status, counter = 0;

	fprintf(stdout, "#cisfun$ ");
	while (getline(&getline_buff, &getline_len, stdin) != -1)
	{
		count = counter = 0;
		while (getline_buff[count] != '\n')
		{
			if (getline_buff[count] == ' ' && counter == 0)
			{
				count++;
				continue;
			}
			buffer[counter] = getline_buff[count];
			count++;
			counter++;
		}
		buffer[counter] = '\0';
		arg = tokenize(buffer);
		my_pid = fork();
		if (my_pid == -1)
		{
			perror("Error: Failed to fork.\n");
			break;
		}
		if (my_pid == 0)
		{
			execve(buffer, arg, env);
			fprintf(stdout, "./shell: No such file or directory\n");
			return (1);
		}
		waitpid(my_pid, &status, 0);
		fprintf(stdout, "#cisfun$ ");
	}
	free(getline_buff);
	return (0);
}

/**
 * tokenize - Initializes the argument list.
 * @buffer: Array containing cmd line input.
 *
 * Return: A pointer to the new argument list.
 */
char **tokenize(char *buffer)
{
	char *token, **arg;
	int count, elements;

	count = 0;
	elements = 3;
	if (buffer == NULL || buffer[0] == '\0')
	{
		arg = malloc(sizeof(char *) * 2);
		arg[0] = "";
		arg[1] = NULL;
	}
	else
	{
		token = strtok(buffer, " ");
		if (token != NULL)
		{
			arg = malloc(sizeof(char *) * 2);
			while (token != NULL)
			{
				arg[count] = token;
				token = strtok(NULL, " ");
				if (token != NULL)
					arg = realloc(arg, elements++);
				count++;
			}
			arg[count] = NULL;
		}
		else
			return (NULL);
	}

	return (arg);
}
