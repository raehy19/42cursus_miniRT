/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_calculate1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:19:32 by rjeong            #+#    #+#             */
/*   Updated: 2023/08/20 20:19:33 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_point	cal_outer_product(t_point const *a, t_point const *b)
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

t_point	cal_ray(int *x, int *y, t_point const *camera)
{
	t_point	outer_product;
	t_point	z;

	z = (t_point) {0,0,1};
	outer_product = cal_outer_product(camera, &z);
	if (outer_product.x == 0 && outer_product.y == 0)
	{
		;
	}
	else
	{
		;
	}
}