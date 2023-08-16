/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_set_data1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:30:01 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/16 17:30:03 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

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
