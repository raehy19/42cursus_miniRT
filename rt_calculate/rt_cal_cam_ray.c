/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cal_cam_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:19:32 by rjeong            #+#    #+#             */
/*   Updated: 2023/08/20 20:19:33 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_point	cal_ray(int *x, int *y, t_camera const *camera)
{
	t_point	ret;
	t_point	outer_prod;
	t_point	z;
	double	theta;

	z = (t_point){0, 0, 1};
	outer_prod = normalize_vec(cal_outer_prod(&camera->vec, &z));
	if (outer_prod.x == 0 && outer_prod.y == 0 && outer_prod.z == 0)
		outer_prod.x = 1;
	theta = (camera->fov / 2) * (*x - (WIDTH / 2)) / (WIDTH / 2)
		* M_PI / 180;
	ret = add_vec(multiply_vec(cos(theta), camera->vec),
			multiply_vec(sin(theta), outer_prod));
	outer_prod = normalize_vec(cal_outer_prod(&camera->vec, &outer_prod));
	if (*x % 20 == 0 && *y % 20 == 0)
	{
		printf(" / theta width : %lf / %lf / ", theta, theta / M_PI * 180);
		printf(" / outer product : %lf %lf %lf / ", outer_prod.x, outer_prod.y, outer_prod.z);
	}
	theta = (camera->fov / 2 * (HEIGHT / WIDTH))
		* ((HEIGHT / 2) - *y) / (HEIGHT / 2) * M_PI / 180;
	if (*x % 20 == 0 && *y % 20 == 0)
	{
		printf(" / theta height : %lf / %lf / ", theta, theta / M_PI * 180);
		printf(" / outer product : %lf %lf %lf / ", outer_prod.x, outer_prod.y, outer_prod.z);
	}
	ret = add_vec(multiply_vec(cos(theta), ret),
//	ret = add_vec( ret,
			multiply_vec(sin(theta), outer_prod));
	return (ret);
}