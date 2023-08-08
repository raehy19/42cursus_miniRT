/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:36:33 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/08 17:38:29 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	rt_init(int ac, char **av, t_minirt *list);
void	rt_check_arg(int ac, char **av);
int		rt_open_file(char *filename);
void	rt_set_data_from_file(int fd, t_minirt *list);
int		rt_is_strchr(char *s, char c);
char	*rt_getline(int fd);
char	*rt_eof_check(char **rest, char *line, int read_len);
int		rt_read_line(int fd, char *buffer, char **rest);
int		rt_rl_strchr(const char *s, int c);
char	*rt_strndup(char *buffer, ssize_t len);
char	*rt_line_check(char **rest);
int		rt_check_identifier(char *line, t_minirt *list);
int		rt_is_identifier(char *line, char *identifier, int len);
int		rt_set_ambient_lightning(char *line, t_minirt *list);
int		rt_set_camera(char *line, t_minirt *list);
int		rt_set_light(char *line, t_minirt *list);
int		rt_set_plain(char *line, t_minirt *list);
int		rt_set_sphere(char *line, t_minirt *list);
int		rt_set_cylinder(char *line, t_minirt *list);
int		rt_set_float(char *line, int *i, float *tmp);
int		rt_set_point(char *line, int *i, t_point *tmp);
int		rt_set_color(char *line, int *i, t_color *tmp);
int		rt_try_atoi(char *line, int *i, int *j, int *res);
int		rt_try_atof(char *line, int *i, int *j, float *res);
int		rt_check_minus(char c, int *k, int *m);
int		rt_try_atof_before_dot(char *line, int *k, float *res);
int		rt_try_atof_after_dot(char *line, int *k, float *res, float _res);
int		rt_check_basic_data(t_minirt *list);
int		rt_error_msg(char *s, int status);

int	check_list(t_minirt *list)
{
	printf("----------    test init    ----------\n");
	printf("ambient\t[%f] [%d,%d,%d]\n", list->ambient.ratio, list->ambient.color.red, list->ambient.color.green, list->ambient.color.blue);
	printf("camera\t[%f,%f,%f] [%f,%f,%f] [%f]\n", list->camera.loc.x, list->camera.loc.y, list->camera.loc.z, list->camera.vec.x, list->camera.vec.y, list->camera.vec.z, list->camera.fov);
	printf("light\t[%f,%f,%f] [%f] [%d,%d,%d]\n", list->light.loc.x, list->light.loc.y, list->light.loc.z, list->light.ratio, list->light.color.red, list->light.color.green, list->light.color.blue);
	printf("----------    test over    ----------\n");
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_minirt	list;

	rt_init(ac, av, &list);
	check_list(&list);
//	system("leaks miniRT");
	return (SUCCESS);
}

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

int	rt_check_identifier(char *line, t_minirt *list)
{
	if (rt_is_identifier(line, "A", 1))
		rt_set_ambient_lightning(line, list);
	else if (rt_is_identifier(line, "C", 1))
		rt_set_camera(line, list);
	else if (rt_is_identifier(line, "L", 1))
		rt_set_light(line, list);
	else if (rt_is_identifier(line, "pl", 2))
		rt_set_plain(line, list);
	else if (rt_is_identifier(line, "sp", 2))
		rt_set_sphere(line, list);
	else if (rt_is_identifier(line, "cy", 2))
		rt_set_cylinder(line, list);
	else
		return (rt_error_msg("syntax error on line", 1));
	return (SUCCESS);
}

int	rt_is_identifier(char *line, char *identifier, int len)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] != '\0' && rt_is_strchr(" \t", line[i]))
		i++;
	j = 0;
	while (j < len)
	{
		if (line[i + j] != identifier[j])
			return (FALSE);
		j++;
	}
	if (line[i + j] == ' ' || line[i + j] == '\t')
		return (TRUE);
	return (FALSE);
}

int	rt_set_ambient_lightning(char *line, t_minirt *list)
{
	int			i;

	if (list->count[AMBIENT] != 0)
		rt_error_msg("just one ambient lightning is required!", 1);
	list->count[AMBIENT] += 1;
	i = 0;
	while (line[i] != '\0' && rt_is_strchr(" \t", line[i]))
		i++;
	i++;
	if (rt_set_float(line, &i, &list->ambient.ratio))
		return (rt_error_msg("syntax error on line A's ratio", 1));
	if (rt_set_color(line, &i, &list->ambient.color))
		return (rt_error_msg("syntax error on line A's color", 1));
	return (SUCCESS);
}

int	rt_set_camera(char *line, t_minirt *list)
{
	int			i;

	if (list->count[CAMERA] != 0)
		rt_error_msg("just one camera is required!", 1);
	list->count[CAMERA] += 1;
	i = 0;
	while (line[i] != '\0' && rt_is_strchr(" \t", line[i]))
		i++;
	i++;
	if (rt_set_point(line, &i, &list->camera.loc))
		return (rt_error_msg("syntax error on line C's location", 1));
	if (rt_set_point(line, &i, &list->camera.vec))
		return (rt_error_msg("syntax error on line C's Vector", 1));
	if (rt_set_float(line, &i, &list->camera.fov))
		return (rt_error_msg("syntax error on line C's fov", 1));
	return (SUCCESS);
}

int	rt_set_light(char *line, t_minirt *list)
{
	int			i;

	if (list->count[LIGHT] != 0)
		rt_error_msg("just one light is required!", 1);
	list->count[LIGHT] += 1;
	i = 0;
	while (line[i] != '\0' && rt_is_strchr(" \t", line[i]))
		i++;
	i++;
	if (rt_set_point(line, &i, &list->light.loc))
		return (rt_error_msg("syntax error on line L's location", 1));
	if (rt_set_float(line, &i, &list->light.ratio))
		return (rt_error_msg("syntax error on line L's ratio", 1));
	if (rt_set_color(line, &i, &list->light.color))
		return (rt_error_msg("syntax error on line L's color", 1));
	return (SUCCESS);
}

int	rt_set_plain(char *line, t_minirt *list)
{
	t_plane	tmp;
	int		i;

	list->count[PLAIN] += 1;
	ft_memset(&tmp, 0, 0);
	list = (t_minirt *)list;
	i = 0;
	while (line[i] != '\0' && rt_is_strchr(" \t", line[i]))
		i++;
	i += 2;
	if (rt_set_point(line, &i, &tmp.loc))
		return (rt_error_msg("syntax error on line pl's location", 1));
	if (rt_set_point(line, &i, &tmp.vec))
		return (rt_error_msg("syntax error on line pl's vactor", 1));
	if (rt_set_color(line, &i, &tmp.color))
		return (rt_error_msg("syntax error on line pl's color", 1));
	return (SUCCESS);
}

int	rt_set_sphere(char *line, t_minirt *list)
{
	t_sphere	tmp;
	int			i;

	list->count[SPHERE] += 1;
	ft_memset(&tmp, 0, 0);
	list = (t_minirt *)list;
	i = 0;
	while (line[i] != '\0' && rt_is_strchr(" \t", line[i]))
		i++;
	i += 2;
	if (rt_set_point(line, &i, &tmp.loc))
		return (rt_error_msg("syntax error on line sp's location", 1));
	if (rt_set_float(line, &i, &tmp.diameter))
		return (rt_error_msg("syntax error on line sp's diameter", 1));
	if (rt_set_color(line, &i, &tmp.color))
		return (rt_error_msg("syntax error on line sp's color", 1));
	return (SUCCESS);
}

int	rt_set_cylinder(char *line, t_minirt *list)
{
	t_cylinder	tmp;
	int			i;

	list->count[CYLINDER] += 1;
	ft_memset(&tmp, 0, 0);
	list = (t_minirt *)list;
	i = 0;
	while (line[i] != '\0' && rt_is_strchr(" \t", line[i]))
		i++;
	i += 2;
	if (rt_set_point(line, &i, &tmp.loc))
		return (rt_error_msg("syntax error on line cy's location", 1));
	if (rt_set_point(line, &i, &tmp.vec))
		return (rt_error_msg("syntax error on line cy's vactor", 1));
	if (rt_set_float(line, &i, &tmp.diameter))
		return (rt_error_msg("syntax error on line cy's diameter", 1));
	if (rt_set_float(line, &i, &tmp.height))
		return (rt_error_msg("syntax error on line cy's height", 1));
	if (rt_set_color(line, &i, &tmp.color))
		return (rt_error_msg("syntax error on line cy's color", 1));
	return (SUCCESS);
}

int	rt_set_float(char *line, int *i, float *tmp)
{
	int		j;
	float	res;

	while (line[*i] != '\0' && rt_is_strchr(" \t", line[*i]))
		*i += 1;
	j = 0;
	if (rt_try_atof(line, i, &j, &res))
		return (FAIL);
	*tmp = res;
	*i = *i + j;
	return (SUCCESS);
}

int	rt_set_point(char *line, int *i, t_point *tmp)
{
	int		j;
	float	res;

	while (line[*i] != '\0' && rt_is_strchr(" \t", line[*i]))
		*i += 1;
	j = 0;
	if (rt_try_atof(line, i, &j, &res))
		return (FAIL);
	tmp->x = res;
	if (line[*i + j] != ',')
		return (FAIL);
	j += 1;
	if (rt_try_atof(line, i, &j, &res))
		return (FAIL);
	tmp->y = res;
	if (line[*i + j] != ',')
		return (FAIL);
	j += 1;
	if (rt_try_atof(line, i, &j, &res))
		return (FAIL);
	tmp->z = res;
	*i = *i + j;
	return (SUCCESS);
}

int	rt_set_color(char *line, int *i, t_color *tmp)
{
	int	j;
	int	res;

	while (line[*i] != '\0' && rt_is_strchr(" \t", line[*i]))
		*i += 1;
	j = 0;
	if (rt_try_atoi(line, i, &j, &res))
		return (FAIL);
	tmp->red = res;
	if (line[*i + j] != ',')
		return (FAIL);
	j += 1;
	if (rt_try_atoi(line, i, &j, &res))
		return (FAIL);
	tmp->green = res;
	if (line[*i + j] != ',')
		return (FAIL);
	j += 1;
	if (rt_try_atoi(line, i, &j, &res))
		return (FAIL);
	tmp->blue = res;
	*i = *i + j;
	return (SUCCESS);
}

int	rt_try_atoi(char *line, int *i, int *j, int *res)
{
	int	k;

	k = 0;
	*res = 0;
	while (line[*i + *j + k] != '\0')
	{
		if (rt_is_strchr(" \t,", line[*i + *j + k]))
			break ;
		if (ft_isdigit(line[*i + *j + k]) == 0)
			return (FAIL);
		*res *= 10;
		*res += line[*i + *j + k] - '0';
		k += 1;
	}
	if (k == 0)
		return (FAIL);
	*j += k;
	return (SUCCESS);
}

int	rt_try_atof(char *line, int *i, int *j, float *res)
{
	int		k;
	int		m;

	*res = 0;
	if (rt_check_minus(line[*i + *j], &k, &m))
		return (FAIL);
	if (rt_try_atof_before_dot(&line[*i + *j], &k, res))
		return (FAIL);
	if (line[*i + *j + k] == '.')
	{
		k += 1;
		if (rt_try_atof_after_dot(&line[*i + *j], &k, res, 0))
			return (FAIL);
	}
	if ((m == 1 && k == 0) || (m == -1 && k == 1))
		return (FAIL);
	*j += k;
	*res *= m;
	return (SUCCESS);
}

int	rt_check_minus(char c, int *k, int *m)
{
	if (c == '\0')
		return (FAIL);
	*k = 0;
	*m = 1;
	if (c == '-')
	{
		*m = -1;
		*k = 1;
	}
	return (SUCCESS);
}

int	rt_try_atof_before_dot(char *line, int *k, float *res)
{
	while (line[*k] != 0)
	{
		if (rt_is_strchr(" \t,.", line[*k]))
			break ;
		if (ft_isdigit(line[*k]) == 0)
			return (FAIL);
		*res *= 10;
		*res += line[*k] - '0';
		*k += 1;
	}
	return (SUCCESS);
}

int	rt_try_atof_after_dot(char *line, int *k, float *res, float _res)
{
	int	last;
	int	i;

	i = 0;
	last = 0;
	while (rt_is_strchr(" \t,", line[*k + last]) == FALSE)
		last++;
	while (i < last)
	{
		if (ft_isdigit(line[*k + last - i - 1]) == 0)
			return (FAIL);
		_res /= 10;
		_res += line[*k + last - i - 1] - '0';
		i += 1;
	}
	*res = *res + _res/10;
	*k += last;
	return (SUCCESS);
}

int	rt_check_basic_data(t_minirt *list)
{
	if (list->count[AMBIENT] == 0)
		rt_error_msg("one ambient lightning is required!", 1);
	if (list->count[CAMERA] == 0)
		rt_error_msg("one camera is required!", 1);
	if (list->count[LIGHT] == 0)
		rt_error_msg("one light is required!", 1);
	return (SUCCESS);
}

int	rt_error_msg(char *s, int status)
{
	write(2, "Error\n", 6);
	write(2, "miniRT : ", 9);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	exit(status);
	return (status);
}
