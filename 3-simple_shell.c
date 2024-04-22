#include "main.h"

#define BUFFER_SIZE 2048

char **tokenize(char *buffer, const char *delimiter);
int forking(pid_t my_pid, char **arg, char **env, int *status);

/**
 * main - Entry point to the function.
 *
 * Return: 0 if program runs successfully.
 */
int main(void)
{
	char *getline_buff = NULL, buffer[BUFFER_SIZE], temp[BUFFER_SIZE], *slash;
	char **env = environ, **arg, **path;
	pid_t my_pid;
	size_t getline_len = 0;
	int count = 0, status, counter = 0;

	slash = "/";
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
		if (buffer[0] != '/' && buffer[0] != '.')
		{
			path = tokenize(getenv("PATH"), ":");
			if (sprintf(temp, "%s%s", slash, buffer) <= 0)
			{
				perror("Error: sprintf failed.\n");
				break;
			}
			count = 0;
			while (path[count] != NULL)
			{
				if (sprintf(buffer, "%s%s", path[count], temp) > 0)
				{
					arg = tokenize(buffer, " ");
					my_pid = fork();
					if (forking(my_pid, arg, env, &status) == 0)
					{
						free(arg);
						free(getline_buff);
						fprintf(stdout, "#cisfun$ ");
						break;
					}
				}
				else
				{
					perror("Error: sprintf failed.\n");
					break;
				}
				count++;
				if (path[count] == NULL)
				{
					fprintf(stdout, "./shell: No such file or directory\n");
					free(arg);
					free(getline_buff);
					fprintf(stdout, "#cisfun$ ");
				}
			}
			continue;
		}
		else
		{
			arg = tokenize(buffer, " ");
			my_pid = fork();
			forking(my_pid, arg, env, &status);
			free(arg);
			free(getline_buff);
			fprintf(stdout, "#cisfun$ ");
		}
	}
	return (0);
}

/**
 * tokenize - Initializes the argument list.
 * @buffer: Array containing cmd line input.
 * @delimiter: String denoting end of token.
 *
 * Return: A pointer to the new argument list.
 */
char **tokenize(char *buffer, const char *delimiter)
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
		token = strtok(buffer, delimiter);
		if (token != NULL)
		{
			arg = malloc(sizeof(char *) * 2);
			while (token != NULL)
			{
				arg[count] = token;
				token = strtok(NULL, delimiter);
				if (token != NULL)
				{
					arg = realloc(arg, sizeof(char *) * elements);
					elements++;
				}
				count++;
			}
			arg[count] = NULL;
		}
		else
			return (NULL);
	}

	return (arg);
}

/**
 * forking - Handles processes occuring after forking.
 * @my_pid: Process ID of the running program.
 * @arg: Double pointer to the argument list to be passed to arg[0].
 * @env: Double pointer to the env. variable list.
 * @status: Pointer to waitpid() integer return value.
 *
 * Return: 0 if program runs successfully, -1 if not.
 */
int forking(pid_t my_pid, char **arg, char **env, int *status)
{
	int value;

	value = 0;
	if (my_pid == -1)
	{
		perror("Error: Failed to fork.\n");
		value = 0;
	}
	else if (my_pid == 0)
	{
		execve(arg[0], arg, env);
		value = -1;
	}
	else
		waitpid(my_pid, status, 0);

	return (value);
}
