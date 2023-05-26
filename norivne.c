#include "shell.h"

/**
 * _myenv - prints the current environ
 * @inf: this struct has potential arguments prototype.
 * Return: Always 0
 */
int _myenv(info_t *inf)
{
	print_list_str(inf->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ for variable
 * @info: this struct having potential arguments.
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *y;

	while (node)
	{
		y = starts_with(node->str, name);
		if (y && *y)
			return (y);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv -   Initialize a fresh environment variable,
 *             or update an existing one
 * @inf: this struct having potential arguments.
 *  Return: Always 0
 */
int _mysetenv(info_t *inf)
{
	if (inf->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv -  delete an environment variable
 * @info: this struct having potential arguments.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int h;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (h = 1; h <= info->argc; h++)
		_unsetenv(info, info->argv[h]);

	return (0);
}

/**
 * populate_env_list -this  populates env linked list
 * @infro: this structure having potential arguments
 * Return: Always 0
 */
int populate_env_list(info_t *infro)
{
	list_t *node = NULL;
	size_t g;

	for (g = 0; environ[g]; g++)
		add_node_end(&node, environ[g], 0);
	infro->env = node;
	return (0);
}

