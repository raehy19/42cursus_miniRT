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

double	cal_distance(t_point const p1, t_point const p2)
{
	return (sqrt(pow(p1.x - p2.x, 2)
			+ pow(p1.y - p2.y, 2)
			+ pow(p1.z - p2.z, 2)));
}

t_ray	cal_hit_point(double q1, double q2, t_ray const *cam, t_point const *sp)
{
	t_ray	ret;
	t_point	p1;
	t_point	p2;

	p1.x = cam->start.x + q1 * cam->vec.x;
	p1.y = cam->start.y + q1 * cam->vec.y;
	p1.z = cam->start.z + q1 * cam->vec.z;
	p2.x = cam->start.x + q2 * cam->vec.x;
	p2.y = cam->start.y + q2 * cam->vec.y;
	p2.z = cam->start.z + q2 * cam->vec.z;
	if (cal_distance(p1, cam->start) < cal_distance(p2, cam->start))
		ret.start = p1;
	else
		ret.start = p2;
	ret.vec.x = ret.start.x - sp->x;
	ret.vec.y = ret.start.y - sp->y;
	ret.vec.z = ret.start.z - sp->z;
	return (ret);
}

int	cal_equation(t_sphere const *sphere, t_ray const *cam, t_ray *ret)
{
	t_q_e_c	coef;

	coef.a = pow(cam->vec.x, 2) + pow(cam->vec.y, 2) + pow(cam->vec.z, 2);
	coef.b = 2 * (cam->vec.x * (cam->start.x - sphere->loc.x)
			+ cam->vec.y * (cam->start.y - sphere->loc.y)
			+ cam->vec.z * (cam->start.z - sphere->loc.z));
	coef.c = pow(sphere->loc.x - cam->start.x, 2)
		+ pow(sphere->loc.y - cam->start.y, 2)
		+ pow(sphere->loc.z - cam->start.z, 2)
		- pow(sphere->diameter, 2);
	coef.d = pow(coef.b, 2) - 4 * coef.a * coef.c;
//	printf("// a b c d : %lf :: %lf :: %lf :: %lf //\n", coef.a, coef.b, coef.c, coef.d);
	if (coef.d < 0)
		return (0);
	*ret = cal_hit_point((-coef.b + sqrt(coef.d)) / (2 * coef.a),
			(-coef.b - sqrt(coef.d)) / (2 * coef.a),
			cam, &sphere->loc);
	return (1);
}

int	cal_sphere(t_sphere const *s_list, t_ray *cam, t_ray *hit_point)
{
//	t_ray	ret;
	t_ray	temp;


	while (s_list)
	{
//		printf("sphere : %lf %lf %lf %lf\n",s_list->loc.x, s_list->loc.y, s_list->loc.z, s_list->diameter);
//		printf("cam vec : %lf %lf %lf\ncam loc: %lf %lf %lf\n", cam->vec.x, cam->vec.y, cam->vec.z, cam->start.x, cam->start.y, cam->start.z);

		if (cal_equation(s_list, cam, &temp))
		{
			*hit_point = temp;
			return (1);
		}
		s_list = s_list->next;
	}
	return (0);
}
