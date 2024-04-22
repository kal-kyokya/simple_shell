#include "shell.h"

/**
 * str_tok - extract tokens from strings
 * @str: string to be parsed
 * @delim: symbol separating one piece of data from the other.
 *
 * Return: pointer to the next token, or NULL if there are no
 * more tokens.
 */
char *str_tok(char *str, const char *delim)
{
	static char *token;
	char *token_start;

	if (str != NULL)
		token = str;
	if (token == NULL)
		return (NULL);
	while (*token != '\0' && (strchr(delim, *token)) != NULL)
		token++;
	if (*token == '\0')
		return (NULL);
	token_start = token;
	while (*token != '\0' && (strchr(delim, *token)) == NULL)
		token++;
	if (*token != '\0')
	{
		*token = '\0';
		token++;
	}

	return (strdup(token_start));
}
