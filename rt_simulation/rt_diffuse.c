/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_diffuse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:03:25 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/17 14:03:27 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_point	rt_get_vec(t_point const a, t_point const b);
double	rt_inner_prod(t_point const a, t_point const b);

t_color	rt_add_diffuse_light(t_light *l, t_ray hit, t_color obj)
{
	t_color	tmp;
	double	diffuse;

	ft_memset(&tmp, 0, sizeof(t_color));
	diffuse = rt_get_diffuse_light(l, hit);
	if (diffuse > 0)
	{
		if (obj.red < l->color.red * l->ratio * diffuse)
			tmp.red += (int)obj.red;
		else
			tmp.red += (int)(l->color.red * l->ratio * diffuse);
		if (obj.green < l->color.green * l->ratio * diffuse)
			tmp.green += (int)obj.green;
		else
			tmp.green += (int)(l->color.green * l->ratio * diffuse);
		if (obj.blue < l->color.blue * l->ratio * diffuse)
			tmp.blue += (int)obj.blue;
		else
			tmp.blue += (int)(l->color.blue * l->ratio * diffuse);
	}
	return (tmp);
}

double	rt_get_diffuse_light(t_light *l, t_ray hit)
{
	double	diffuse;
	t_point	vec;
	double	tmp1;
	double	tmp2;

	vec = rt_get_vec(l->loc, hit.loc);
	tmp1 = sqrt(pow(hit.vec.x, 2) + pow(hit.vec.y, 2) + pow(hit.vec.z, 2));
	tmp2 = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	diffuse = (rt_inner_prod(vec, hit.vec) / tmp1) / tmp2;
	return (diffuse);
}

t_point	rt_get_vec(t_point const a, t_point const b)
{
	t_point	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

double	rt_inner_prod(t_point const a, t_point const b)
{
	double	res;

	res = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return (res);
}
