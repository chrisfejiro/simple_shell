#include "shell.h"

/**
 * list_len - determines length of linked list
 * @hg: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *hg)
{
	size_t i = 0;

	while (hg)
	{
		hg = hg->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @headg: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *headg)
{
	list_t *node = headg;
	size_t i = list_len(headg), j;
	char **strs;
	char *str;

	if (!headg || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @hg: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *hg)
{
	size_t i = 0;

	while (hg)
	{
		_puts(convert_number(hg->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hg->str ? hg->str : "(nil)");
		_puts("\n");
		hg = hg->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @cg: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char cg)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((cg == -1) || (*p == cg)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @nodeg: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *nodeg)
{
	size_t i = 0;

	while (head)
	{
		if (head == nodeg)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

