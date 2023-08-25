/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ambient.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:58:21 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/16 18:58:22 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	rt_add_ambient_light(t_ambient *amb, int *c, t_color tmp, t_color obj)
{
	tmp.tr = 0;
	tmp.red += (int)(amb->color.red * amb->ratio);
	tmp.green += (int)(amb->color.green * amb->ratio);
	tmp.blue += (int)(amb->color.blue * amb->ratio);
	if (obj.red < tmp.red)
		tmp.red = obj.red;
	if (obj.green < tmp.green)
		tmp.green = obj.green;
	if (obj.blue < tmp.blue)
		tmp.blue = obj.blue;
	rt_add_light_color(tmp, c);
	return (SUCCESS);
}
