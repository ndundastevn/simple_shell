#include "myshell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t m = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		m = getline(buf, &len_p, stdin);
#else
		m = _getline(info, buf, &len_p);
#endif
		if (m > 0)
		{
			if ((*buf)[m - 1] == '\n')
			{
				(*buf)[m - 1] = '\0';
				m--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_histo_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = m;
				info->cmd_buf = buf;
			}
		}
	}
	return (m);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t m = 0;
	char **buf_p = &(info->arg), *p;

	_eputcharr(BUF_FLUSH);
	m = input_buf(info, &buf, &len);
	if (m == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chainnow(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chainnow(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (m);
}


/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: m
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t m = 0;

	if (*i)
		return (0);
	m = read(info->readfd, buf, READ_BUF_SIZE);
	if (m >= 0)
		*i = m;
	return (m);
}


/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: n
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t m = 0, n = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		n = *length;
	if (i == len)
		i = len = 0;

	m = read_buf(info, buf, &len);
	if (m == -1 || (m == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, n, n ? n + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (n)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	n += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = n;
	*ptr = p;
	return (n);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_eputsft("\n");
	_eputsft("$ ");
	_eputcharr(BUF_FLUSH);
}
