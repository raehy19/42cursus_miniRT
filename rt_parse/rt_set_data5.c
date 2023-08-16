/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_set_data5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:29:48 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/16 17:29:51 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	rt_add_plane_node(t_minirt *list, t_plane *new)
{
	t_plane	*tmp;

	if (list->plane == (void *)0)
		list->plane = new;
	else
	{
		tmp = list->plane;
		while (tmp->next != (void *)0)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (SUCCESS);
}

int	rt_add_sphere_node(t_minirt *list, t_sphere *new)
{
	t_sphere	*tmp;

	if (list->sphere == (void *)0)
		list->sphere = new;
	else
	{
		tmp = list->sphere;
		while (tmp->next != (void *)0)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (SUCCESS);
}

int	rt_add_cylinder_node(t_minirt *list, t_cylinder *new)
{
	t_cylinder	*tmp;

	if (list->cylinder == (void *)0)
		list->cylinder = new;
	else
	{
		tmp = list->cylinder;
		while (tmp->next != (void *)0)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (SUCCESS);
}
