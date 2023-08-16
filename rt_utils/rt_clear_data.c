/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_clear_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:29:39 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/16 17:29:41 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	rt_clear_data(t_minirt *list)
{
	rt_clear_plane_node(list, (void *)0);
	rt_clear_sphere_node(list, (void *)0);
	rt_clear_cylinder_node(list, (void *)0);
	return (SUCCESS);
}

int	rt_clear_plane_node(t_minirt *list, t_plane *tmpp)
{
	tmpp = list->plane;
	while (tmpp != (void *)0)
	{
		list->plane = tmpp->next;
		free(tmpp);
		tmpp = list->plane;
	}
	return (SUCCESS);
}

int	rt_clear_sphere_node(t_minirt *list, t_sphere *tmps)
{
	tmps = list->sphere;
	while (tmps != (void *)0)
	{
		list->sphere = tmps->next;
		free(tmps);
		tmps = list->sphere;
	}
	return (SUCCESS);
}

int	rt_clear_cylinder_node(t_minirt *list, t_cylinder *tmpc)
{
	tmpc = list->cylinder;
	while (tmpc != (void *)0)
	{
		list->cylinder = tmpc->next;
		free(tmpc);
		tmpc = list->cylinder;
	}
	return (SUCCESS);
}
