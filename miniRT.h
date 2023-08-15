/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:36:53 by jijeong           #+#    #+#             */
/*   Updated: 2023/08/08 17:38:33 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>
# include "libft/libft.h"

# define FALSE 0
# define TRUE 1

# define FAIL 1
# define SUCCESS 0

# define AMBIENT 0
# define CAMERA 1
# define LIGHT 2
# define PLAIN 3
# define SPHERE 4
# define CYLINDER 5

# define HEIGHT 800
# define WIDTH 1000

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}			t_point;

typedef struct s_color
{
	int	red;
	int	blue;
	int	green;
}		t_color;

typedef struct s_ambient
{
	float	ratio;
	t_color	color;
}			t_ambient;

typedef struct s_camera
{
	t_point	loc;
	t_point	vec;
	float	fov;
}			t_camera;

typedef struct s_light
{
	t_point	loc;
	float	ratio;
	t_color	color;
}			t_light;

typedef struct s_plane
{
	t_point			loc;
	t_point			vec;
	t_color			color;
	struct s_plane	*next;
}					t_plane;

typedef struct s_sphere
{
	t_point			loc;
	float			diameter;
	t_color			color;
	struct s_sphere	*next;
}					t_sphere;

typedef struct s_cylinder
{
	t_point				loc;
	t_point				vec;
	float				diameter;
	float				height;
	t_color				color;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct s_minirt
{
	int			count[6];
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
}				t_minirt;

typedef struct s_mlxlist
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			linel;
	int			endian;
}				t_mlxlist;

#endif
