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

int	rt_add_ambient_light(t_ambient *ambient, int *color, t_color tmp)
{
	tmp.tr = 0;
	tmp.red += (int)(ambient->color.red * ambient->ratio);
	tmp.green += (int)(ambient->color.green * ambient->ratio);
	tmp.blue += (int)(ambient->color.blue * ambient->ratio);
	if (tmp.red < 0)
		tmp.red = 0;
	if (255 < tmp.red)
		tmp.red = 255;
	if (tmp.green < 0)
		tmp.green = 0;
	if (255 < tmp.green)
		tmp.green = 255;
	if (tmp.blue < 0)
		tmp.blue = 0;
	if (255 < tmp.blue)
		tmp.blue = 255;
	*color += ((ambient->color.tr << 24) + (tmp.red << 16) + \
		(tmp.green << 8) + (tmp.blue));
	return (SUCCESS);
}
