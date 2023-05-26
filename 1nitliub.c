#include "shell.h"

/**
 * _myhistory - shows the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @inform:  this struct having  potential a prototype.
 *  Return: 0 always
 */
int _myhistory(info_t *inform)
{
	print_list(inform->history);
	return (0);
}

/**
 * unset_alias - sets alias to string in code
 * @info: the parameter structure of code
 * @str:  string alias
 *
 * Return: success 0,  error 1.
 */
int unset_alias(info_t *info, char *str)
{
	char *g, s;
	int ret;

	g = _strchr(str, '=');
	if (!g)
		return (1);
	s = *g;
	*g = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*g = s;
	return (ret);
}

/**
 * set_alias - code sets alias to string
 * @info: parameter structure
 * @str: string alias
 *
 * Return: on success 0, on error 1
 */
int set_alias(info_t *info, char *str)
{
	char *k;

	k = _strchr(str, '=');
	if (!k)
		return (1);
	if (!*++k)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias -prints an alias string in the code
 * @node: alias node
 *
 * Return: on success 0, 1 on error
 */
int print_alias(list_t *node)
{
	char *f = NULL, *b = NULL;

	if (node)
	{
		f = _strchr(node->str, '=');
		for (b = node->str; b <= f; b++)
		_putchar(*b);
		_putchar('\'');
		_puts(f + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias – imitate the alias builtin (man alias)
 * @info: the structure having arguments to maintain function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int x = 0;
	char *j = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (x = 1; info->argv[x]; x++)
	{
		j = _strchr(info->argv[x], '=');
		if (j)
			set_alias(info, info->argv[x]);
		else
			print_alias(node_starts_with(info->alias, info->argv[x], '='));
	}

	return (0);
}

