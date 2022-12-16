#include "shell.h"

/**
 * _myhistory - displays the history list.
 * @info: Structure containing potential arguments.
 * Return: 0 for expected results
 **/
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: string alias
 * Return: 0 for expected result
 **/
int unset_alias(info_t *info, char *str)
{
	char *p, cstr;
	int opt;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	cstr = *p;
	*p = 0;
	opt = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = cstr;
	return (opt);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: string alias
 * Return: 0 for expected results
 **/
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 * Return: 0 for expected results
 **/
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments.
 * Return: 0 for expected results
 **/
int _myalias(info_t *info)
{
	int adw = 0;
	char *p = NULL;
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
	for (adw = 1; info->argv[adw]; adw++)
	{
		p = _strchr(info->argv[adw], '=');
		if (p)
			set_alias(info, info->argv[adw]);
		else
			print_alias(node_starts_with(info->alias, info->argv[adw], '='));
	}

	return (0);
}
