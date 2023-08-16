/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:29:30 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/16 17:29:36 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	rt_print_list_data(t_minirt *list)
{
	printf("----------    t_minirt list printer init    ----------\n");
	printf("ambient\t[%f] [%d,%d,%d]\n", list->ambient.ratio, \
	list->ambient.color.red, \
	list->ambient.color.green, \
	list->ambient.color.blue);
	printf("camera\t[%f,%f,%f] [%f,%f,%f] [%d]\n", \
	list->camera.loc.x, list->camera.loc.y, list->camera.loc.z, \
	list->camera.vec.x, list->camera.vec.y, list->camera.vec.z, \
	list->camera.fov);
	printf("light\t[%f,%f,%f] [%f] [%d,%d,%d]\n", \
	list->light.loc.x, list->light.loc.y, list->light.loc.z, \
	list->light.ratio, \
	list->light.color.red, list->light.color.green, list->light.color.blue);
	rt_print_plane_list_data(list, (void *)0);
	rt_print_sphere_list_data(list, (void *)0);
	rt_print_cylinder_list_data(list, (void *)0);
	printf("----------    t_minirt list printer over    ----------\n");
	return (SUCCESS);
}

int	rt_print_plane_list_data(t_minirt *list, t_plane *tmpp)
{
	int	i;

	i = 0;
	tmpp = list->plane;
	while (tmpp != (void *)0)
	{
		printf("plane[%d]\t[%f,%f,%f] [%f,%f,%f] [%d,%d,%d] [%p]\n", i, \
		tmpp->loc.x, tmpp->loc.y, tmpp->loc.z, \
		tmpp->vec.x, tmpp->vec.y, tmpp->vec.z, \
		tmpp->color.red, tmpp->color.green, tmpp->color.blue, tmpp->next);
		tmpp = tmpp->next;
		i += 1;
	}
	return (SUCCESS);
}

int	rt_print_sphere_list_data(t_minirt *list, t_sphere *tmps)
{
	int	i;

	i = 0;
	tmps = list->sphere;
	while (tmps != (void *)0)
	{
		printf("sphere[%d]\t[%f,%f,%f] [%f] [%d,%d,%d] [%p]\n", i, \
		tmps->loc.x, tmps->loc.y, tmps->loc.z, \
		tmps->diameter, \
		tmps->color.red, tmps->color.green, tmps->color.blue, tmps->next);
		tmps = tmps->next;
		i += 1;
	}
	return (SUCCESS);
}

int	rt_print_cylinder_list_data(t_minirt *list, t_cylinder *tmpc)
{
	int	i;

	i = 0;
	tmpc = list->cylinder;
	while (tmpc != (void *)0)
	{
		printf("cylinder[%d]\t", i);
		printf("[%f,%f,%f] [%f,%f,%f] [%f] [%f] [%d,%d,%d] [%p]\n", \
		tmpc->loc.x, tmpc->loc.y, tmpc->loc.z, \
		tmpc->vec.x, tmpc->vec.y, tmpc->vec.z, \
		tmpc->diameter, tmpc->height, \
		tmpc->color.red, tmpc->color.green, tmpc->color.blue, tmpc->next);
		tmpc = tmpc->next;
		i += 1;
	}
	return (SUCCESS);
}
