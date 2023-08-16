/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_set_data3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:29:54 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/16 17:29:57 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	rt_set_int(char *line, int *i, int *tmp)
{
	int	j;
	int	res;

	while (line[*i] != '\0' && rt_is_strchr(" \t", line[*i]))
		*i += 1;
	j = 0;
	if (rt_try_atoi(line, i, &j, &res))
		return (FAIL);
	*tmp = res;
	*i = *i + j;
	return (SUCCESS);
}

int	rt_set_float(char *line, int *i, double *tmp)
{
	int		j;
	double	res;

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
	double	res;

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
