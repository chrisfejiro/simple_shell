#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @ne: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int ne)
{
	unsigned int i;

	for (i = 0; i < ne; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - frees a string of strings
 * @ppe: string of strings
 */
void ffree(char **ppe)
{
	char **a = ppe;

	if (!ppe)
		return;
	while (*ppe)
		free(*ppe++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptre: pointer to previous mallocated block
 * @old_size: byte size of previous block
 * @new_size:size of new block in byte
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptre, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptre)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptre), NULL);
	if (new_size == old_size)
		return (ptre);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptre)[old_size];
	free(ptre);
	return (p);
}
