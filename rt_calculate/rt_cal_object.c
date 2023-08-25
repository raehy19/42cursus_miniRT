/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cal_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:28:58 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/25 15:29:01 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	cal_object(t_minirt *list, t_ray *cam, t_ray *hit_point)
{
	int	flag;

	flag = 0;
	flag = cal_sphere(list->sphere, cam, hit_point, flag);
	flag = cal_plane(list->plane, cam, hit_point, flag);
	flag = cal_cylinder(list->cylinder, cam, hit_point, flag);
	return (flag);
}

int	check_object(t_minirt *list, t_ray *hit)
{
	int	flag;

	flag = 0;
	flag = check_sphere(list->sphere, hit, list->light.loc, flag);
	flag = check_plane(list->plane, hit, list->light.loc, flag);
	flag = check_cylinder(list->cylinder, hit, list->light.loc, flag);
	return (flag);
}
