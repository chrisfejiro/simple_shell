#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@srct: the source string
 *@p: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *srct, int p)
{
	int w, j;
	char *s = dest;

	w = 0;
	while (srct[w] != '\0' && w < p - 1)
	{
		dest[w] = srct[w];
		w++;
	}
	if (w < p)
	{
		j = w;
		while (j < p)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@desti: the first string
 *@srct: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *desti, char *srct, int n)
{
	int y, j;
	char *s = desti;

	y = 0;
	j = 0;
	while (desti[y] != '\0')
		y++;
	while (srct[j] != '\0' && j < n)
	{
		desti[y] = srct[j];
		y++;
		j++;
	}
	if (j < n)
		desti[y] = '\0';
	return (s);
}

/**
 * *_strchr - searches and finds chars
 * @t: the string to be parsed
 * @k: the char to be found
 * Return: s a pointer to area a
 */
char *_strchr(char *t, char k)
{
	do {
		if (*t == k)
			return (t);
	} while (*t++ != '\0');

	return (NULL);
}
