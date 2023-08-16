/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:30:16 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/16 17:30:26 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	rt_init(int ac, char **av, t_minirt *list)
{
	int	fd;

	rt_check_arg(ac, av);
	ft_memset(list, 0, sizeof(t_minirt));
	fd = rt_open_file(av[1]);
	rt_set_data_from_file(fd, list);
	close(fd);
	fd = 0;
	rt_check_basic_data(list);
}

void	rt_check_arg(int ac, char **av)
{
	int	len;

	if (ac != 2)
		rt_error_msg("only one argument required!", 1);
	len = ft_strlen(av[1]);
	if (len < 4)
		rt_error_msg("filename error! too short", 1);
	if (len < 4 || ft_strncmp(".rt", &av[1][len - 3], 4))
		rt_error_msg("filename error! *.rt needed", 1);
}

int	rt_open_file(char *filename)
{
	int		fd;
	char	buffer;

	fd = open(filename, O_RDONLY);
	if (-1 == fd)
	{
		perror("miniRT");
		exit(1);
	}
	if (read(fd, &buffer, 0) == -1)
	{
		perror("miniRT");
		exit(1);
	}
	return (fd);
}

void	rt_set_data_from_file(int fd, t_minirt *list)
{
	char	*line;
	int		i;

	while (1)
	{
		i = 0;
		line = rt_getline(fd);
		printf("getline : [%s]\n", line);
		if (line == (void *)0)
			break ;
		while (line[i] != '\0' && rt_is_strchr(" \t", line[i]))
			i++;
		if (line[i] != '\0')
			rt_check_identifier(line, list);
		free(line);
	}
}
