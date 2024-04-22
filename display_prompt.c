#include "shell.h"

/**
 * display_prompt - Prompts user to input command.
 *
 * Return: Nothing.
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		fprintf(stdout, "#cisfun$ ");
}
