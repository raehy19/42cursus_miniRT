/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 21:37:07 by rjeong            #+#    #+#             */
/*   Updated: 2023/08/21 21:37:09 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"


t_ray	cal_hit_point(double q1, double q2, t_ray const *cam, t_point const *sp)
{
	t_ray	ret;
	t_point	p1;
	t_point	p2;

	p1.x = cam->loc.x + q1 * cam->vec.x;
	p1.y = cam->loc.y + q1 * cam->vec.y;
	p1.z = cam->loc.z + q1 * cam->vec.z;
	p2.x = cam->loc.x + q2 * cam->vec.x;
	p2.y = cam->loc.y + q2 * cam->vec.y;
	p2.z = cam->loc.z + q2 * cam->vec.z;
	if (cal_distance(p1, cam->loc) < cal_distance(p2, cam->loc))
		ret.loc = p1;
	else
		ret.loc = p2;
	ret.vec.x = ret.loc.x - sp->x;
	ret.vec.y = ret.loc.y - sp->y;
	ret.vec.z = ret.loc.z - sp->z;
	return (ret);
}

int	cal_equation(t_sphere const *sphere, t_ray const *cam, t_ray *ret)
{
	t_q_e_c	coef;

	coef.a = pow(cam->vec.x, 2) + pow(cam->vec.y, 2) + pow(cam->vec.z, 2);
	coef.b = 2 * (cam->vec.x * (cam->loc.x - sphere->loc.x)
			+ cam->vec.y * (cam->loc.y - sphere->loc.y)
			+ cam->vec.z * (cam->loc.z - sphere->loc.z));
	coef.c = pow(sphere->loc.x - cam->loc.x, 2)
		+ pow(sphere->loc.y - cam->loc.y, 2)
		+ pow(sphere->loc.z - cam->loc.z, 2)
		- pow(sphere->diameter, 2);
	coef.d = pow(coef.b, 2) - 4 * coef.a * coef.c;
	if (coef.d < 0)
		return (0);
	*ret = cal_hit_point((-coef.b + sqrt(coef.d)) / (2 * coef.a),
			(-coef.b - sqrt(coef.d)) / (2 * coef.a),
			cam, &sphere->loc);
	if (rt_inner_prod(rt_get_vec(ret->loc, cam->loc), cam->vec) < 0)
		return (0);
	return (1);
}

int	cal_sphere(t_sphere *list, t_ray *cam, t_ray *hit_point, int flag)
{
	t_ray	temp;

	while (list)
	{
		if (cal_equation(list, cam, &temp))
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

int	check_sphere(t_sphere *list, t_ray *cam, int flag)
{
	t_ray	temp;

	while (list)
	{
		if (cal_equation(list, cam, &temp))
		{
			if (flag == 0)
				flag = 1;
		}
		list = list->next;
	}
	return (flag);
}
