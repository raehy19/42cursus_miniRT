/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mlx_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:29:24 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/16 17:29:26 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	rt_set_mlx(t_mlxlist *mlx)
{
	ft_memset(mlx, 0, sizeof(t_mlxlist));
	mlx->mlx = mlx_init();
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, \
	&mlx->linel, &mlx->endian);
	printf("[%p][%d, %d, %d][%lu]\n", mlx->addr, mlx->bpp, mlx->linel, \
	mlx->endian, sizeof(int));
	return (SUCCESS);
}

int	rt_get_img(t_mlxlist *mlx, t_minirt *list)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			color = 0;
			if (rt_get_pixel_color(list, j, i, &color) == FAIL)
				return (rt_error_msg("something wrong in simulation", 1));
			rt_mlx_pixel_put(mlx, j, i, color);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	rt_get_pixel_color(t_minirt *list, int a, int b, int *color)
{
	int			hitflag[2];
	t_color		tmpcolor;
	t_ray		ray;
	t_ray		hit_point;
	t_color		objcolor = {0,255,255,255};

	ray.loc = list->camera.loc;
	ray.vec = cal_ray(&a, &b, &list->camera);
	if (a % 20 == 0 && b % 20 == 0)
		printf("/ view %d, %d : %lf , %lf , %lf\n", a, b, ray.vec.x, ray.vec.y, ray.vec.z);
	ft_memset(&tmpcolor, 0, sizeof(t_color));
	hitflag[0] = cal_sphere(list->sphere, &ray, &hit_point);
	if (hitflag[0])
	{
		hitflag[1] = FALSE;
		if (hitflag[1] == FALSE)
			tmpcolor = rt_add_diffuse_light(&list->light, hit_point, objcolor);
		rt_add_ambient_light(&list->ambient, color, tmpcolor);
	}
	else
		rt_add_light_color(tmpcolor, color);
	return (SUCCESS);
}

int	rt_display_mlx(t_mlxlist *mlx, char *name)
{
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, name);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_hook(mlx->win, 2, 0, rt_keyhook, mlx);
	mlx_hook(mlx->win, 17, 0, rt_end, mlx);
	mlx_loop(mlx->mlx);
	return (SUCCESS);
}

void	rt_mlx_pixel_put(t_mlxlist *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->linel + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}
