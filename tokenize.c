#include "shell.h"

#define ARRAY_SIZE 16

/**
 * tokenize - Turns each word of a string input into an char array[] element.
 * @input: String to be processed.
 * @delimiter: String denoting limit between words.
 *
 * Return: A double pointer to the tokenized version of input.
 */
char **tokenize(char *input, const char *delimiter)
{
	char **argv = NULL;
	char *token;
	int count, max_size;

	count = 0;
	max_size = ARRAY_SIZE;
	argv = malloc(sizeof(char *) * max_size);
	if (argv == NULL)
		return (NULL);
	token = strtok(input, delimiter);
	if (token == NULL)
		return (NULL);
	while (token != NULL)
	{
		argv[count] = token;
		token = strtok(NULL, delimiter);
		count++;
		if (count >= max_size - 1)
		{
			max_size *= 2;
			argv = realloc(argv, sizeof(char *) * max_size);
			if (argv == NULL)
				return (NULL);
		}
	}
	argv[count] = NULL;

	return (argv);
}
