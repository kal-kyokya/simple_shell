#include "shell.h"

/**
 * get_path - gets the full path of the given command.
 *@argv: the commad inputed.
 *
 * Return: return path.
 */
char *get_path(char **argv)
{
	char *paths, *paths_copy, *token, *path_name = NULL;
	int argv_index0_len, path_len;
	struct stat st;

	if (argv == NULL || argv[0] == NULL)
		return (NULL);
	paths = getenv("PATH");
	if (paths == NULL)
		return (NULL);
	paths_copy = strdup(paths);
	if (paths_copy == NULL)
		return (NULL);
	argv_index0_len = strlen(argv[0]);
	token = strtok(paths_copy, ":");
	while (token)
	{
		path_len = strlen(token);
		path_name = malloc(argv_index0_len + path_len + 2);
		if (path_name == NULL)
			return (NULL);
		strcpy(path_name, token);
		strcat(path_name, "/");
		strcat(path_name, argv[0]);
		if (stat(path_name, &st) == 0)
		{
			free(paths_copy);
			return (path_name);
		}
		free(path_name);
		token = strtok(NULL, ":");
	}
	free(paths_copy);
	if (access(argv[0], X_OK) == 0)
		return (argv[0]);
	return (NULL);
}
