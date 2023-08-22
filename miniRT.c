/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:36:33 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/08 17:38:29 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int ac, char **av)
{
	t_minirt	list;
	t_mlxlist	mlx;

	rt_init(ac, av, &list);
	rt_print_list_data(&list);
	rt_set_mlx(&mlx);
	rt_get_img(&mlx, &list);
	rt_clear_data(&list);
	rt_display_mlx(&mlx, av[0]);
	return (SUCCESS);
}
