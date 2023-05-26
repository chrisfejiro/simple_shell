#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @infor: struct address
 */
void clear_info(info_t *infor)
{
	infor->arg = NULL;
	infor->argv = NULL;
	infor->path = NULL;
	infor->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @infor: struct address
 * @av: argument vector
 */
void set_info(info_t *infor, char **av)
{
	int i = 0;

	infor->fname = av[0];
	if (infor->arg)
	{
		infor->argv = strtow(infor->arg, " \t");
		if (!infor->argv)
		{
			infor->argv = malloc(sizeof(char *) * 2);
			if (infor->argv)
			{
				infor->argv[0] = _strdup(infor->arg);
				infor->argv[1] = NULL;
			}
		}
		for (i = 0; infor->argv && infor->argv[i]; i++)
			;
		infor->argc = i;

		replace_alias(infor);
		replace_vars(infor);
	}
}

/**
 * free_info - frees info_t struct fields
 * @infor: struct address
 * @allr: true if freeing all fields
 */
void free_info(info_t *infor, int allr)
{
	ffree(infor->argv);
	infor->argv = NULL;
	infor->path = NULL;
	if (allr)
	{
		if (!infor->cmd_buf)
			free(infor->arg);
		if (infor->env)
			free_list(&(infor->env));
		if (infor->history)
			free_list(&(infor->history));
		if (infor->alias)
			free_list(&(infor->alias));
		ffree(infor->environ);
			infor->environ = NULL;
		bfree((void **)infor->cmd_buf);
		if (infor->readfd > 2)
			close(infor->readfd);
		_putchar(BUF_FLUSH);
	}
}

