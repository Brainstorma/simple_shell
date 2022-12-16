#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 * Return: 1 for expected result
 **/
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 **/
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int fint = 0, sint = 0;

	for (sint = 0, fint = start; fint < stop; fint++)
		if (pathstr[fint] != ':')
			buf[sint++] = pathstr[fint];
	buf[sint] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 * Return: full path of cmd
 **/
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int fint = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[fint] || pathstr[fint] == ':')
		{
			path = dup_chars(pathstr, curr_pos, fint);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[fint])
				break;
			curr_pos = fint;
		}
		fint++;
	}
	return (NULL);
}
