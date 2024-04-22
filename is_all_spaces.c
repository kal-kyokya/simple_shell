#include "shell.h"

/**
 * is_all_spaces - Checks if the input is made of space characters only.
 * @input: String input received from the user through stdin.
 * @read: The number of bytes read from a getline() call.
 *
 * Return: Boolean TRUE or FALSE.
 */
bool is_all_spaces(char *input, ssize_t read)
{
	int count;

	count = 0;
	while (input[count] == ' ')
	{
		count++;
		if (count == read - 1)
			return (true);
	}

	return (false);
}
