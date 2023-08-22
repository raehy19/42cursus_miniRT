/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_check_data1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:29:43 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/16 17:29:47 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	rt_check_basic_data(t_minirt *list)
{
	if (list->count[AMBIENT] == 0)
		rt_error_msg("one ambient lightning is required!", 1);
	if (list->count[CAMERA] == 0)
		rt_error_msg("one camera is required!", 1);
	if (list->count[LIGHT] == 0)
		rt_error_msg("one light is required!", 1);
	rt_check_ambient_range(list->ambient);
	rt_check_camera_range(list->camera);
	rt_check_light_range(list->light);
	rt_check_sphere_range(list->sphere);
	rt_check_plane_range(list->plane);
	rt_check_cylinder_range(list->cylinder);
	return (SUCCESS);
}

int	rt_check_ambient_range(t_ambient ambient)
{
	if (ambient.ratio < 0.0 || 1.0 < ambient.ratio)
		rt_error_msg("ambient lighting ratio range error!", 1);
	if (ambient.color.red < 0 || 255 < ambient.color.red)
		rt_error_msg("ambient color red range error!", 1);
	if (ambient.color.green < 0 || 255 < ambient.color.green)
		rt_error_msg("ambient color green range error!", 1);
	if (ambient.color.blue < 0 || 255 < ambient.color.blue)
		rt_error_msg("ambient color blue range error!", 1);
	return (SUCCESS);
}

int	rt_check_camera_range(t_camera camera)
{
	if (camera.fov < 0.0 || 180.0 < camera.fov)
		rt_error_msg("camera fov range error!", 1);
	if (camera.vec.x < -1.0 || 1.0 < camera.vec.x)
		rt_error_msg("camera vec x range error!", 1);
	if (camera.vec.y < -1.0 || 1.0 < camera.vec.y)
		rt_error_msg("camera vec y range error!", 1);
	if (camera.vec.z < -1.0 || 1.0 < camera.vec.z)
		rt_error_msg("camera vec z range error!", 1);
	return (SUCCESS);
}

int	rt_check_light_range(t_light light)
{
	if (light.ratio < 0.0 || 1.0 < light.ratio)
		rt_error_msg("light brightness ratio range error!", 1);
	if (light.color.red < 0 || 255 < light.color.red)
		rt_error_msg("light color red range error!", 1);
	if (light.color.green < 0 || 255 < light.color.green)
		rt_error_msg("light color green range error!", 1);
	if (light.color.blue < 0 || 255 < light.color.blue)
		rt_error_msg("light color blue range error!", 1);
	return (SUCCESS);
}
