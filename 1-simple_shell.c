#include "main.h"

#define BUFFER_SIZE 64

/**
 * main - Entry point to the function.
 * @argc: Number of cmd line inputs.
 * @argv: String list of all cmd line inputs.
 *
 * Return: 0 if program runs successfully.
 */
int main(int argc, char **argv __attribute__ ((unused)))
{
	char *getline_buff, buffer[BUFFER_SIZE], **env, *arg[2];
	pid_t my_pid;
	size_t getline_len;
	int count, status;

	env = environ;
	getline_buff = NULL;
	getline_len = count = 0;
	if (argc != 1)
	{
		perror("Usage: ./shell\n");
		return (-1);
	}
	fprintf(stdout, "#cisfun$ ");
	while (getline(&getline_buff, &getline_len, stdin) != -1)
	{
		count = 0;
		while (getline_buff[count] != '\n')
		{
			if (getline_buff[count] == ' ')
			{
				fprintf(stdout, "No space character allowed, one was detected.\n");
				fprintf(stdout, "#cisfun$ ");
				count = -1;
				break;
			}
			buffer[count] = getline_buff[count];

			count++;
		}
		buffer[count] = '\0';
		arg[0] = buffer;
		arg[1] = NULL;
		if (count == -1)
			continue;
		my_pid = fork();
		if (my_pid == -1)
		{
			perror("Error: Failed to fork.\n");
			free(getline_buff);
			return (-1);
		}
		if (my_pid == 0)
		{
			execve(buffer, arg, env);
			fprintf(stdout, "./shell: No such file or directory\n");
			return (1);
		}

		if (my_pid != 0)
		{
			waitpid(my_pid, &status, 0);
			getline_buff = NULL;
			fprintf(stdout, "#cisfun$ ");
		}
	}

	free(getline_buff);
	return (0);
}
