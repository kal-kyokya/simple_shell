#include "shell.h"

/**
 * get_line - reads an entire line from stream
 * @input: pointer to address of the buffer containing the text
 * @len: size in bytes
 * @file: pointer to a file / stream
 *
 * Return: number of characters read.
 */
ssize_t get_line(char **input, size_t *len, FILE *file)
{
	static char buffer[1024];
	static size_t position;
	static ssize_t char_read;
	int chr;
	size_t line_size;

	line_size = 0;
	if (*input == NULL || *len == 0)
	{
		*len = 128;
		*input = (char *)malloc(*len);
		if (*input == NULL)
			return (-1);
	}
	while (1)
	{
		if (position >= (size_t)char_read)
		{
			position = 0;
			char_read = read(fileno(file), buffer, sizeof(buffer));
			if (char_read <= 0)
			{
				if (line_size > 0)
					return (line_size);
				else
					return (-1);
			}
		}
		chr = buffer[position++];
		if (chr == '\n')
			return (line_size);
		if (line_size == *len - 1)
		{
			*len *= 2;
			*input = (char *)realloc(*input, *len);
			if (*input == NULL)
				return (-1);
		}
		(*input)[line_size++] = (char)chr;
	}
}
