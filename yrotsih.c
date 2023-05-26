#include "shell.h"

/**
 * get_history_file - gets the history file
 * @infor: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *infor)
{
	char *bufr, *dirr;

	dirr = _getenv(infor, "HOME=");
	if (!dirr)
		return (NULL);
	bufr = malloc(sizeof(char) * (_strlen(dirr) + _strlen(HIST_FILE) + 2));
	if (!bufr)
		return (NULL);
	bufr[0] = 0;
	_strcpy(bufr, dirr);
	_strcat(bufr, "/");
	_strcat(bufr, HIST_FILE);
	return (bufr);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @infor: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *infor)
{
	ssize_t fdr;
	char *filename = get_history_file(infor);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fdr = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fdr == -1)
		return (-1);
	for (node = infor->history; node; node = node->next)
	{
		_putsfd(node->str, fdr);
		_putfd('\n', fdr);
	}
	_putfd(BUF_FLUSH, fdr);
	close(fdr);
	return (1);
}

/**
 * read_history - reads history from file
 * @infor: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *infor)
{
	int i, last = 0, linecount = 0;
	ssize_t fdr, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(infor);

	if (!filename)
		return (0);

	fdr = open(filename, O_RDONLY);
	free(filename);
	if (fdr == -1)
		return (0);
	if (!fstat(fdr, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fdr, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fdr);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(infor, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(infor, buf + last, linecount++);
	free(buf);
	infor->histcount = linecount;
	while (infor->histcount-- >= HIST_MAX)
		delete_node_at_index(&(infor->history), 0);
	renumber_history(infor);
	return (infor->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @infor: Structure having potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *infor, char *buf, int linecount)
{
	list_t *node = NULL;

	if (infor->history)
		node = infor->history;
	add_node_end(&node, buf, linecount);

	if (!infor->history)
		infor->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history associated list after changes
 * @infor: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *infor)
{
	list_t *node = infor->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (infor->histcount = i);
}
