/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_set_data2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:29:58 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/16 17:30:00 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	rt_set_plain(char *line, t_minirt *list)
{
	t_plane	*tmp;
	int		i;

	list->count[PLAIN] += 1;
	tmp = (t_plane *)malloc(sizeof(t_plane));
	ft_memset(tmp, 0, sizeof(t_plane));
	list = (t_minirt *)list;
	i = 0;
	while (line[i] != '\0' && rt_is_strchr(" \t", line[i]))
		i++;
	i += 2;
	if (rt_set_point(line, &i, &tmp->loc))
		return (rt_error_msg("syntax error on line pl's location", 1));
	if (rt_set_point(line, &i, &tmp->vec))
		return (rt_error_msg("syntax error on line pl's vactor", 1));
	if (rt_set_color(line, &i, &tmp->color))
		return (rt_error_msg("syntax error on line pl's color", 1));
	rt_add_plane_node(list, tmp);
	return (SUCCESS);
}

int	rt_set_sphere(char *line, t_minirt *list)
{
	t_sphere	*tmp;
	int			i;

	list->count[SPHERE] += 1;
	tmp = (t_sphere *)malloc(sizeof(t_sphere));
	ft_memset(tmp, 0, sizeof(t_sphere));
	list = (t_minirt *)list;
	i = 0;
	while (line[i] != '\0' && rt_is_strchr(" \t", line[i]))
		i++;
	i += 2;
	if (rt_set_point(line, &i, &tmp->loc))
		return (rt_error_msg("syntax error on line sp's location", 1));
	if (rt_set_float(line, &i, &tmp->diameter))
		return (rt_error_msg("syntax error on line sp's diameter", 1));
	if (rt_set_color(line, &i, &tmp->color))
		return (rt_error_msg("syntax error on line sp's color", 1));
	rt_add_sphere_node(list, tmp);
	return (SUCCESS);
}

int	rt_set_cylinder(char *line, t_minirt *list)
{
	t_cylinder	*tmp;
	int			i;

	list->count[CYLINDER] += 1;
	tmp = (t_cylinder *)malloc(sizeof(t_cylinder));
	ft_memset(tmp, 0, sizeof(t_cylinder));
	list = (t_minirt *)list;
	i = 0;
	while (line[i] != '\0' && rt_is_strchr(" \t", line[i]))
		i++;
	i += 2;
	if (rt_set_point(line, &i, &tmp->loc))
		return (rt_error_msg("syntax error on line cy's location", 1));
	if (rt_set_point(line, &i, &tmp->vec))
		return (rt_error_msg("syntax error on line cy's vactor", 1));
	if (rt_set_float(line, &i, &tmp->diameter))
		return (rt_error_msg("syntax error on line cy's diameter", 1));
	if (rt_set_float(line, &i, &tmp->height))
		return (rt_error_msg("syntax error on line cy's height", 1));
	if (rt_set_color(line, &i, &tmp->color))
		return (rt_error_msg("syntax error on line cy's color", 1));
	tmp->h_loc = add_vec(tmp->loc, multiply_vec(tmp->height, \
		normalize_vec(tmp->vec)));
	rt_add_cylinder_node(list, tmp);
	return (SUCCESS);
}
