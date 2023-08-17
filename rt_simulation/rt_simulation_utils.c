/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_simulation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:45:30 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/17 14:45:32 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	rt_add_light_color(t_color tmp, int *color)
{
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
	*color += (tmp.tr << 24) + (tmp.red << 16);
	*color += (tmp.green << 8) + (tmp.blue);
	return (SUCCESS);
}
