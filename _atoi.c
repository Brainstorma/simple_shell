#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 * Return: 1 if interactive mode, 0 otherwise
 **/

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 **/

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is a letter else 0
 **/

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 for expected results
 **/

int _atoi(char *s)
{
	int scon, sign = 1, f = 0, out;
	unsigned int oput = 0;

	for (scon = 0;  s[scon] != '\0' && f != 2; scon++)
	{
		if (s[scon] == '-')
			sign *= -1;

		if (s[scon] >= '0' && s[scon] <= '9')
		{
			f = 1;
			oput *= 10;
			oput += (s[scon] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (sign == -1)
		out = -oput;
	else
		out = oput;

	return (out);
}
