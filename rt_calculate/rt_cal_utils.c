/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:15:04 by rjeong            #+#    #+#             */
/*   Updated: 2023/08/22 18:15:05 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_point	cal_outer_prod(t_point const *a, t_point const *b)
{
	t_point	ret;

	ret.x = (a->y * b->z - a->z * b->y);
	ret.y = (a->z * b->x - a->x * b->z);
	ret.z = (a->x * b->y - a->y * b->x);
	return (ret);
}

t_point	normalize_vec(t_point a)
{
	double	temp;

	temp = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
	if (temp != 0)
	{
		a.x /= temp;
		a.y /= temp;
		a.z /= temp;
	}
	return (a);
}

t_point	add_vec(t_point const a, t_point const b)
{
	t_point	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

t_point	sub_vec(t_point const a, t_point const b)
{
	t_point	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

t_point	multiply_vec(double const mul, t_point const vec)
{
	t_point	ret;

	ret.x = vec.x * mul;
	ret.y = vec.y * mul;
	ret.z = vec.z * mul;
	return (ret);
}
