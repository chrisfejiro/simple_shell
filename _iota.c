#include "shell.h"

/**
 * interactive - returns code true if shell is in discussion mode
 * @info: the address structure
 *
 * Return: if discussion in mode return 1, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim -  if character is a delimeter
 * @k: character  to check
 * @delimeter: delimeter string
 * Return: if true return 1, if false return 0
 */
int is_delim(char k, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == k)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character in order
 * @c: The character  input
 * Return: if c is alphabetic return 1, otherwise return 0
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi – string conversion to integer
 * @l:  converted string
 * Return:  if no numbers in string return 0, otherwise converted number
 */

int _atoi(char *l)
{
	int p, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (p = 0; l[p] != '\0' && flag != 2; p++)
	{
		if (l[p] == '-')
			sign *= -1;

		if (l[p] >= '0' && l[p] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (l[p] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
