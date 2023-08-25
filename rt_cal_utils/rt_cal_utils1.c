/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cal_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:15:04 by rjeong            #+#    #+#             */
/*   Updated: 2023/08/22 18:15:05 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

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

t_point	multiply_vec(double const mul, t_point const vec)
{
	t_point	ret;

	ret.x = vec.x * mul;
	ret.y = vec.y * mul;
	ret.z = vec.z * mul;
	return (ret);
}

double	cal_distance(t_point const p1, t_point const p2)
{
	return (sqrt(pow(p1.x - p2.x, 2)
			+ pow(p1.y - p2.y, 2)
			+ pow(p1.z - p2.z, 2)));
}
