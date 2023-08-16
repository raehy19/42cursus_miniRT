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

int	rt_ambient_light(t_ambient *ambient, int *color)
{
	*color += ((ambient->color.tr << 24) + \
		((int)(ambient->color.red * ambient->ratio) << 16) + \
		((int)(ambient->color.green * ambient->ratio) << 8) + \
		((int)(ambient->color.blue * ambient->ratio)));
	return (SUCCESS);
}
