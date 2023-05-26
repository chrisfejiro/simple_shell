#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @ptrr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptrr)
{
	if (ptrr && *ptrr)
	{
		free(*ptrr);
		*ptrr = NULL;
		return (1);
	}
	return (0);
}
