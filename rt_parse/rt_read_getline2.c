/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_read_getline2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:30:03 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/16 17:30:05 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

char	*rt_strndup(char *buffer, ssize_t len)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		str[i] = buffer[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*rt_line_check(char **rest)
{
	char	*line;
	char	*temp;
	int		nl_i;
	int		len;

	line = (void *)0;
	len = 0;
	while (*(*rest + len) != '\0')
		len++;
	nl_i = rt_rl_strchr(*rest, '\n');
	if (nl_i == -1)
		return (line);
	temp = ft_substr(*rest, nl_i + 1, len - nl_i);
	line = ft_substr(*rest, 0, nl_i + 1);
	free(*rest);
	*rest = temp;
	line[nl_i] = '\0';
	return (line);
}
