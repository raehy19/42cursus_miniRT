/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_read_getline1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:30:06 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/16 17:30:15 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	rt_is_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (TRUE);
		i += 1;
	}
	return (FALSE);
}

char	*rt_getline(int fd)
{
	static char	*rest = (void *)0;
	char		*line;
	char		buffer[50];
	int			read_len;

	if (rest == (void *)0)
		rest = ft_strdup("");
	line = rt_line_check(&rest);
	if (line != (void *)0)
		return (line);
	read_len = rt_read_line(fd, buffer, &rest);
	line = rt_line_check(&rest);
	line = rt_eof_check(&rest, line, read_len);
	return (line);
}

char	*rt_eof_check(char **rest, char *line, int read_len)
{
	if (**rest == '\0')
	{
		free(*rest);
		*rest = (void *)0;
	}
	else
	{
		if (line == (void *)0 && read_len == 0)
		{
			line = *rest;
			*rest = (void *)0;
			return (line);
		}
	}
	return (line);
}

int	rt_read_line(int fd, char *buffer, char **rest)
{
	char	*line;
	char	*temp;
	ssize_t	read_len;

	read_len = 1;
	while ((rt_rl_strchr(*rest, '\n') == -1) && read_len)
	{
		read_len = read(fd, buffer, 50);
		line = rt_strndup(buffer, read_len);
		temp = *rest;
		*rest = ft_strjoin(temp, line);
		free(temp);
		free(line);
	}
	return ((int)read_len);
}

int	rt_rl_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*(s + i) != '\0')
	{
		if ((unsigned char)*(s + i) == (unsigned char)c)
			return (i);
		i++;
	}
	return (-1);
}
