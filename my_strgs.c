#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @sr: the string whose length to check as an argument
 *
 * Return: integer length of string
 */
int _strlen(char *sr)
{
	int i = 0;

	if (!sr)
		return (0);

	while (*sr++)
		i++;
	return (i);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @sr1: the first strang
 * @sr2: the second strang
 *
 * Return: negative if sr1 < sr2, positive if sr1 > sr2, zero if sr1 == sr2
 */
int _strcmp(char *sr1, char *sr2)
{
	while (*sr1 && *sr2)
	{
		if (*sr1 != *sr2)
			return (*sr1 - *sr2);
		sr1++;
		sr2++;
	}
	if (*sr1 == *sr2)
		return (0);
	else
		return (*sr1 < *sr2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystackr: string to search
 * @needler: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystackr, const char *needler)
{
	while (*needler)
		if (*needler++ != *haystackr++)
			return (NULL);
	return ((char *)haystackr);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @srcr: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *srcr)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*srcr)
		*dest++ = *srcr++;
	*dest = *srcr;
	return (ret);
}
