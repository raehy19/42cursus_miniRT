/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mlx_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:29:27 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/16 17:29:28 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	rt_keyhook(int k, t_mlxlist *list)
{
	if (k == 53)
		rt_end(list);
	return (0);
}

int	rt_end(t_mlxlist *list)
{
	printf("miniRT : good bye!\n");
	mlx_destroy_window(list->mlx, list->win);
	mlx_destroy_image(list->mlx, list->img);
	system("leaks miniRT"); // we must remove this line before upload 42' repo
	exit(0);
	return (0);
}
