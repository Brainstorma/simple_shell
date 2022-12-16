#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 **/
char *_strncpy(char *dest, char *src, int n)
{
	int fint, sint;
	char *s = dest;

	fint = 0;
	while (src[fint] != '\0' && fint < n - 1)
	{
		dest[fint] = src[fint];
		fint++;
	}
	if (fint < n)
	{
		sint = fint;
		while (sint < n)
		{
			dest[sint] = '\0';
			sint++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 **/
char *_strncat(char *dest, char *src, int n)
{
	int fint, sint;
	char *s = dest;

	fint = 0;
	sint = 0;
	while (dest[fint] != '\0')
		fint++;
	while (src[sint] != '\0' && sint < n)
	{
		dest[fint] = src[sint];
		fint++;
		sint++;
	}
	if (sint < n)
		dest[fint] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 **/
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
