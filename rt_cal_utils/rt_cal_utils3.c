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

int	rt_cal_cy_cos(double *res, t_point p, t_point c, t_point h)
{
	res[0] = rt_inner_prod(rt_get_vec(p, c), rt_get_vec(h, c)) / \
		(cal_distance(p, c) * cal_distance(h, c));
	res[1] = rt_inner_prod(rt_get_vec(p, h), rt_get_vec(c, h)) / \
		(cal_distance(p, h) * cal_distance(c, h));
	return (SUCCESS);
}
