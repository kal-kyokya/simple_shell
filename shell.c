#include "main.h"

#define BUFFER_SIZE 64

/**
 * main - Entry point to the function.
 *
 * Return: 0 if program runs successfully.
 */
int main(void)
{
	char *getline_buff = NULL, buffer[BUFFER_SIZE], **env = environ, *arg[2];
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
		buffer[count] = '\0';
		arg[0] = buffer;
		arg[1] = NULL;
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
