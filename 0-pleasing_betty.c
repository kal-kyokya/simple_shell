#include "main.h"

/**
 * main - Entry point to the program.
 *
 * Return: 0 if program runs successfully.
 */
int main(void)
{
	char *str = "Hello Betty my world ;-)";
	int count;

	count = 0;
	while (*(str + count) != '\0')
	{
		_putchar(str[count]);
		count++;
	}
	_putchar('\n');

	return (0);
}
