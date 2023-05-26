#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @z: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *z)
{
	int i = 0;
	unsigned long int res = 0;

	if (*z == '+')
		z++;  /* TODO: why does this make main return 255? */
	for (i = 0;  z[i] != '\0'; i++)
	{
		if (z[i] >= '0' && z[i] <= '9')
		{
			res *= 10;
			res += (z[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estring: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estring)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estring);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @in: the input
 * @fdi: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int in, int fdi)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fdi == STDERR_FILENO)
		__putchar = _eputchar;
	if (in < 0)
	{
		_abs_ = -in;
		__putchar('-');
		count++;
	}
	else
		_abs_ = in;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @bases: base
 * @flag: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int bases, int flag)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flag & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % bases];
		n /= bases;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to update
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int o;

	for (o = 0; buf[o] != '\0'; o++)
		if (buf[o] == '#' && (!o || buf[o - 1] == ' '))
		{
			buf[o] = '\0';
			break;
		}
}
