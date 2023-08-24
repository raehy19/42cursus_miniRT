/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rotate_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:41:33 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/22 15:41:34 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_point	rt_rotate_x(t_point before, double theta)
{
	t_point	tmp;

	tmp.x = before.x;
	tmp.y = cos(theta) * before.y - sin(theta) * before.z;
	tmp.z = sin(theta) * before.y + cos(theta) * before.z;
	return (tmp);
}

t_point	rt_rotate_y(t_point before, double theta)
{
	t_point	tmp;

	tmp.x = cos(theta) * before.x + sin(theta) * before.z;
	tmp.y = before.y;
	tmp.z = -sin(theta) * before.x + cos(theta) * before.z;
	return (tmp);
}

t_point	rt_rotate_z(t_point before, double theta)
{
	t_point	tmp;

	tmp.x = cos(theta) * before.x - sin(theta) * before.y;
	tmp.y = sin(theta) * before.x + cos(theta) * before.y;
	tmp.z = before.z;
	return (tmp);
}
