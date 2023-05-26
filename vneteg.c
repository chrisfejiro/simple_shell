#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @infor: Structure having potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *infor)
{
	if (!infor->environ || infor->env_changed)
	{
		infor->environ = list_to_strings(infor->env);
		infor->env_changed = 0;
	}

	return (infor->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @infor: Structure having potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @vari: the string env var property
 */
int _unsetenv(info_t *infor, char *vari)
{
	list_t *node = infor->env;
	size_t i = 0;
	char *p;

	if (!node || !vari)
		return (0);

	while (node)
	{
		p = starts_with(node->str, vari);
		if (p && *p == '=')
		{
			infor->env_changed = delete_node_at_index(&(infor->env), i);
			i = 0;
			node = infor->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (infor->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @infor: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @vari: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *infor, char *vari, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!vari || !value)
		return (0);

	buf = malloc(_strlen(vari) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, vari);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = infor->env;
	while (node)
	{
		p = starts_with(node->str, vari);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			infor->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(infor->env), buf, 0);
	free(buf);
	infor->env_changed = 1;
	return (0);
}
