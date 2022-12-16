#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 * Return: pointer to destination
 **/
char *_strcpy(char *dest, char *src)
{
	int fint = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[fint])
	{
		dest[fint] = src[fint];
		fint++;
	}
	dest[fint] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 * Return: pointer to the mirror string
 **/
char *_strdup(const char *str)
{
	int slen = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		slen++;
	ret = malloc(sizeof(char) * (slen + 1));
	if (!ret)
		return (NULL);
	for (slen++; slen--;)
		ret[slen] = *--str;
	return (ret);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 * Return: void
 **/
void _puts(char *str)
{
	int fint = 0;

	if (!str)
		return;
	while (str[fint] != '\0')
	{
		_putchar(str[fint]);
		fint++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: 1 for expected result
 **/
int _putchar(char c)
{
	static int fint;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || fint >= WRITE_BUF_SIZE)
	{
		write(1, buf, fint);
		fint = 0;
	}
	if (c != BUF_FLUSH)
		buf[fint++] = c;
	return (1);
}
