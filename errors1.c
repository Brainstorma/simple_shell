#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 for expected results
 **/
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			res *= 10;
			res += (s[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 for expected results
 **/
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: file descriptor
 * Return: number of characters printed
 **/
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, inc = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		inc++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			inc++;
		}
		current %= i;
	}
	__putchar('0' + current);
	inc++;

	return (inc);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 **/
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 * Return: Always 0;
 **/
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
