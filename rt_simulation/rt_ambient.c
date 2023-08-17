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
	rt_add_light_color(tmp, color);
	return (SUCCESS);
}
