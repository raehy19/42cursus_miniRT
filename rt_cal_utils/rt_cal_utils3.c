/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cal_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:45:30 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/17 14:45:32 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	rt_cal_cy_cos(double *res, t_point *p, t_point c, t_point h)
{
	res[0] = rt_inner_prod(rt_get_vec(p[0], c), rt_get_vec(h, c)) / \
		(cal_distance(p[0], c) * cal_distance(h, c));
	res[1] = rt_inner_prod(rt_get_vec(p[0], h), rt_get_vec(c, h)) / \
		(cal_distance(p[0], h) * cal_distance(c, h));
	res[2] = rt_inner_prod(rt_get_vec(p[1], c), rt_get_vec(h, c)) / \
		(cal_distance(p[1], c) * cal_distance(h, c));
	res[3] = rt_inner_prod(rt_get_vec(p[1], h), rt_get_vec(c, h)) / \
		(cal_distance(p[1], h) * cal_distance(c, h));
	return (SUCCESS);
}

t_point	rt_cal_cy_hit_vec(t_point p, t_point c, t_point h)
{
	t_point	res;

	res = normalize_vec(rt_get_vec(rt_get_vec(p, c), \
		multiply_vec(rt_inner_prod(rt_get_vec(p, c), h), \
		normalize_vec(h))));
	return (res);
}

int	cal_eq_circle(t_ray circle, t_ray *cam, t_ray *ret)
{
	double	t;

	if (rt_inner_prod(circle.vec, cam->vec) == 0)
	{
		if (rt_inner_prod(circle.vec, rt_get_vec(cam->loc, circle.loc)) != 0)
			return (0);
		ret->loc = cam->loc;
		ret->vec = circle.vec;
		return (1);
	}
	t = ((circle.loc.x - cam->loc.x) * circle.vec.x \
		+ (circle.loc.y - cam->loc.y) * circle.vec.y \
		+ (circle.loc.z - cam->loc.z) * circle.vec.z) \
		/ (circle.vec.x * cam->vec.x \
		+ circle.vec.y * cam->vec.y \
		+ circle.vec.z * cam->vec.z);
	ret->loc.x = cam->loc.x + t * cam->vec.x;
	ret->loc.y = cam->loc.y + t * cam->vec.y;
	ret->loc.z = cam->loc.z + t * cam->vec.z;
	ret->vec = circle.vec;
	if (rt_inner_prod(rt_get_vec(ret->loc, cam->loc), cam->vec) < 0)
		return (FALSE);
	return (TRUE);
}
