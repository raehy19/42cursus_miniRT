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
