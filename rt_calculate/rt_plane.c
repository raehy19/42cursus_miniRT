/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:11:08 by rjeong            #+#    #+#             */
/*   Updated: 2023/08/25 15:11:09 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	cal_eq_pl(t_plane const *plane, t_ray const *cam, t_ray *ret)
{
	double	t;

	if (rt_inner_prod(plane->vec, cam->vec) == 0)
	{
		if (rt_inner_prod(plane->vec, rt_get_vec(cam->loc, plane->loc)) != 0)
			return(0);
		ret->loc = cam->loc;
		ret->vec = plane->vec;
		return (1);
	}
	t = ((plane->loc.x - cam->loc.x) * plane->vec.x
		+ (plane->loc.y - cam->loc.y) * plane->vec.y
		+ (plane->loc.z - cam->loc.z) * plane->vec.z)
		/ (plane->vec.x * cam->vec.x
		+ plane->vec.y * cam->vec.y
		+ plane->vec.z * cam->vec.z);
	ret->loc.x = cam->loc.x + t * cam->vec.x;
	ret->loc.y = cam->loc.y + t * cam->vec.y;
	ret->loc.z = cam->loc.z + t * cam->vec.z;
	ret->vec = plane->vec;
	if (rt_inner_prod(rt_get_vec(ret->loc, cam->loc), cam->vec) < 0)
		return (0);
	return (1);
}

int	cal_plane(t_plane *list, t_ray *cam, t_ray *hit_point, int flag)
{
	t_ray	temp;

	while (list)
	{
		if (cal_eq_pl(list, cam, &temp))
		{
			if (flag == 0)
			{
				*hit_point = temp;
				hit_point->col = list->color;
				flag = 1;
			}
			else if (cal_distance(hit_point->loc, cam->loc) \
					> cal_distance(temp.loc, cam->loc))
			{
				*hit_point = temp;
				hit_point->col = list->color;
			}
		}
		list = list->next;
	}
	return (flag);
}

int	check_plane(t_plane *list, t_ray *hit, t_point light, int flag)
{
	t_ray	temp;

	while (list)
	{
		if (cal_eq_pl(list, hit, &temp)
			&& cal_distance(hit->loc,light) > cal_distance(hit->loc, temp.loc))
		{
			if (flag == 0)
				flag = 1;
		}
		list = list->next;
	}
	return (flag);
}


