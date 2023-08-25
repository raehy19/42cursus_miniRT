/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 21:37:07 by rjeong            #+#    #+#             */
/*   Updated: 2023/08/21 21:37:09 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_q_e_c	cal_coef_cy(t_cylinder *cylinder, t_ray *cam)
{
	t_q_e_c	coef;
	t_point	v;
	t_point	w;
	t_point	norm_h;

	v = cam->vec;
	w = rt_get_vec(cam->loc, cylinder->loc);
	norm_h = normalize_vec(cylinder->vec);
	coef.a = rt_inner_prod(v, v) - pow(rt_inner_prod(v, norm_h), 2);
	coef.b = 2 * (rt_inner_prod(v, w) - rt_inner_prod(v, norm_h)
		* rt_inner_prod(w, norm_h));
	coef.c = rt_inner_prod(w, w) - pow(rt_inner_prod(w, norm_h), 2)
		- pow(cylinder->diameter, 2);
	coef.d = pow(coef.b, 2) - 4 * coef.a * coef.c;
	return (coef);
}

int	cal_eq_cy(t_cylinder *cylinder, t_ray *cam, t_ray *ret)
{
	t_q_e_c	coef;

	coef = cal_coef_cy(cylinder, cam);

	(void )ret;
	if (coef.d < 0)
		return (0);
	return (1);
}

int	cal_cylinder(t_cylinder *list, t_ray *cam, t_ray *hit_point, int flag)
{
	t_ray	temp;

	while (list)
	{
		if (cal_eq_cy(list, cam, &temp))
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

int	check_cylinder(t_cylinder *list, t_ray *hit, t_point light, int flag)
{
	t_ray	temp;

	while (list)
	{
		if (cal_eq_cy(list, hit, &temp)
		&& cal_distance(hit->loc,light) > cal_distance(hit->loc, temp.loc))
		{
			if (flag == 0)
				flag = 1;
		}
		list = list->next;
	}
	return (flag);
}
