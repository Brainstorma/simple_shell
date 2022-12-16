#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position
 * Return: 1 for expected result
 **/
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t fv = *p;

	if (buf[fv] == '|' && buf[fv + 1] == '|')
	{
		buf[fv] = 0;
		fv++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[fv] == '&' && buf[fv + 1] == '&')
	{
		buf[fv] = 0;
		fv++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[fv] == ';') /* found end of this command */
	{
		buf[fv] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = fv;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buffer
 * Return: Void
 **/
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t fv = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			fv = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			fv = len;
		}
	}

	*p = fv;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 * Return: 1 for expected result
 **/
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 * Return: 0 for expected result
 **/
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 * Return: 1 for expected result
 **/
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
