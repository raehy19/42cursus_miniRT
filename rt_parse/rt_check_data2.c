/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_check_data2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:29:41 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/16 17:29:42 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	rt_check_sphere_range(t_sphere *sphere)
{
	while (sphere)
	{
		if (sphere->color.red < 0 || 255 < sphere->color.red)
			rt_error_msg("sphere color red range error!", 1);
		if (sphere->color.green < 0 || 255 < sphere->color.green)
			rt_error_msg("sphere color green range error!", 1);
		if (sphere->color.blue < 0 || 255 < sphere->color.blue)
			rt_error_msg("sphere color blue range error!", 1);
		sphere = sphere->next;
	}
	return (SUCCESS);
}

int	rt_check_plane_range(t_plane *plane)
{
	while (plane)
	{
		if (plane->vec.x < -1.0 || 1.0 < plane->vec.x)
			rt_error_msg("plane vec x range error!", 1);
		if (plane->vec.y < -1.0 || 1.0 < plane->vec.y)
			rt_error_msg("plane vec y range error!", 1);
		if (plane->vec.z < -1.0 || 1.0 < plane->vec.z)
			rt_error_msg("plane vec z range error!", 1);
		if (plane->color.red < 0 || 255 < plane->color.red)
			rt_error_msg("plane color red range error!", 1);
		if (plane->color.green < 0 || 255 < plane->color.green)
			rt_error_msg("plane color green range error!", 1);
		if (plane->color.blue < 0 || 255 < plane->color.blue)
			rt_error_msg("plane color blue range error!", 1);
		plane = plane->next;
	}
	return (SUCCESS);
}

int	rt_check_cylinder_range(t_cylinder *cylinder)
{
	while (cylinder)
	{
		if (cylinder->vec.x < -1.0 || 1.0 < cylinder->vec.x)
			rt_error_msg("cylinder vec x range error!", 1);
		if (cylinder->vec.y < -1.0 || 1.0 < cylinder->vec.y)
			rt_error_msg("cylinder vec y range error!", 1);
		if (cylinder->vec.z < -1.0 || 1.0 < cylinder->vec.z)
			rt_error_msg("cylinder vec z range error!", 1);
		if (cylinder->color.red < 0 || 255 < cylinder->color.red)
			rt_error_msg("cylinder color red range error!", 1);
		if (cylinder->color.green < 0 || 255 < cylinder->color.green)
			rt_error_msg("cylinder color green range error!", 1);
		if (cylinder->color.blue < 0 || 255 < cylinder->color.blue)
			rt_error_msg("cylinder color blue range error!", 1);
		cylinder = cylinder->next;
	}
	return (SUCCESS);
}
