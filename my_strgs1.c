#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination in code
 * @srcr: the source original
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *srcr)
{
	int i = 0;

	if (dest == srcr || srcr == 0)
		return (dest);
	while (srcr[i])
	{
		dest[i] = srcr[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @strr: the string to replicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *strr)
{
	int length = 0;
	char *ret;

	if (strr == NULL)
		return (NULL);
	while (*strr++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--strr;
	return (ret);
}

/**
 * _puts - prints an input string
 * @strr: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *strr)
{
	int i = 0;

	if (!strr)
		return;
	while (strr[i] != '\0')
	{
		_putchar(strr[i]);
		i++;
	}
}

/**
 * _putchar - writes the character cr to stdout
 * @cr: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char cr)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (cr == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (cr != BUF_FLUSH)
		buf[i++] = cr;
	return (1);
}

