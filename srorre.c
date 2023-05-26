#include "shell.h"

/**
 * _eputs - prints an input string in code
 * @string: the string to be printed in code
 *
 * Return: Nothing
 */
void _eputs(char *string)
{
	int d = 0;

	if (!string)
		return;
	while (string[d] != '\0')
	{
		_eputchar(string[d]);
		d++;
	}
}

/**
 * _eputchar - writes the character y to stderr
 * @y: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char y)
{
	static int f;
	static char buf[WRITE_BUF_SIZE];

	if (y == BUF_FLUSH || f >= WRITE_BUF_SIZE)
	{
		write(2, buf, f);
		f = 0;
	}
	if (y != BUF_FLUSH)
		buf[f++] = y;
	return (1);
}

/**
 * _putfd - writes the character d to given fdi
 * @d: The character to print
 * @fdi: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char d, int fdi)
{
	static int r;
	static char buf[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || r >= WRITE_BUF_SIZE)
	{
		write(fdi, buf, r);
		r = 0;
	}
	if (d != BUF_FLUSH)
		buf[r++] = d;
	return (1);
}

/**
 * _putsfd - prints an input string
 * @string: the string to be printed
 * @fdi: the file descriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *string, int fdi)
{
	int i = 0;

	if (!string)
		return (0);
	while (*string)
	{
		i += _putfd(*string++, fdi);
	}
	return (i);
}

