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

t_point	multiply_vec(double const mul, t_point const vec)
{
	t_point	ret;

	ret.x = vec.x * mul;
	ret.y = vec.y * mul;
	ret.z = vec.z * mul;
	return (ret);
}

t_point	cal_ray(int *x, int *y, t_camera const *camera)
{
	t_point	ret;
	t_point	outer_prod;
	t_point	z;
	double	theta;

	z = (t_point){0, 0, 1};
	outer_prod = normalize_vec(cal_outer_prod(&camera->vec, &z));
	if (outer_prod.x == 0 && outer_prod.y == 0 && outer_prod.z == 0)
		outer_prod.x = 1;
	theta = (camera->fov / 2) * (*x - (WIDTH / 2)) / (WIDTH / 2)
		* M_PI / 180;
	ret = add_vec(multiply_vec(cos(theta), camera->vec),
			multiply_vec(sin(theta), outer_prod));
	outer_prod = normalize_vec(cal_outer_prod(&camera->vec, &outer_prod));
	if (*x % 20 == 0 && *y % 20 == 0)
	{
		printf(" / theta width : %lf / ", theta);
		printf(" / outer product : %lf %lf %lf / ", outer_prod.x, outer_prod.y, outer_prod.z);
	}
	theta = (camera->fov / 2 * (HEIGHT / WIDTH))
		* ((HEIGHT / 2) - *y) / (HEIGHT / 2) * M_PI / 180;
	if (*x % 20 == 0 && *y % 20 == 0)
	{
		printf(" / theta height : %lf / ", theta);
		printf(" / outer product : %lf %lf %lf / ", outer_prod.x, outer_prod.y, outer_prod.z);
	}
	ret = add_vec(multiply_vec(cos(theta), ret),
			multiply_vec(sin(theta), outer_prod));
	return (ret);
}
