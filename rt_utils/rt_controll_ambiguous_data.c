/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_controll_ambiguous_data.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:40:36 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/22 14:40:37 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	rt_controll_ambiguous_data(t_minirt *list)
{
	rt_controll_ambiguous_cam_vec(list);
	return (SUCCESS);
}

int	rt_controll_ambiguous_cam_vec(t_minirt *list)
{
	t_point		cvec;
	t_plane		*tmpp;
	t_cylinder	*tmpc;

	cvec = list->camera.vec;
	if (cvec.x == 0 && cvec.y == 0 && cvec.z != 0)
	{
		list->camera.vec = rt_rotate_x90(list->camera.vec);
		tmpp = list->plane;
		while (tmpp)
		{
			tmpp->vec = rt_rotate_x90(tmpp->vec);
			tmpp = tmpp->next;
		}
		tmpc = list->cylinder;
		while (tmpc)
		{
			tmpc->vec = rt_rotate_x90(tmpc->vec);
			tmpc = tmpc->next;
		}
	}
	return (SUCCESS);
}

t_point	rt_rotate_x90(t_point before)
{
	t_point tmp;

	tmp.x = before.x;
	tmp.y = -before.z;
	tmp.z = before.y;
	return (tmp);
}
