#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @infor: parameter struct
 * @buff: address of buffer
 * @leng: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *infor, char **buff, size_t *leng)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*leng) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)infor->cmd_buff);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buff, &len_p, stdin);
#else
		r = _getline(infor, buff, &len_p);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			infor->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(infor, *buff, infor->histcount++);
			/* if (_strchr(*buff, ';')) is this a command chain? */
			{
				*leng = r;
				infor->cmd_buf = buff;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @infor: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *infor)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(infor->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(infor, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(infor, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(infor, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			infor->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @infor: parameter struct
 * @buff: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *infor, char *buff, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(infor->readfd, buff, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptri: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptri, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptri;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptri = p;
	return (s);
}

/**
 * sigintHandler -ctrl-C blocks
 * @sig_num: signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

