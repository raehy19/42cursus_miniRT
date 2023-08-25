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

# define HEIGHT 800.0
# define WIDTH 1000.0

// quadratic equation coefficients
typedef struct s_q_e_c
{
	double a;
	double b;
	double c;
	double d;
}			t_q_e_c;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}			t_point;

typedef struct s_color
{
	int	tr;
	int	red;
	int	blue;
	int	green;
}		t_color;

typedef struct s_ray
{
	t_point	loc;
	t_point	vec;
	t_color	col;
}			t_ray;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}			t_ambient;

typedef struct s_camera
{
	t_point	loc;
	t_point	vec;
	int		fov;
}			t_camera;

typedef struct s_light
{
	t_point	loc;
	double	ratio;
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
	double			diameter;
	t_color			color;
	struct s_sphere	*next;
}					t_sphere;

typedef struct s_cylinder
{
	t_point				loc;
	t_point				vec;
	double				diameter;
	double				height;
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

// rt_parse/
// rt_read_file.c
void	rt_init(int ac, char **av, t_minirt *list);
void	rt_check_arg(int ac, char **av);
int		rt_open_file(char *filename);
void	rt_set_data_from_file(int fd, t_minirt *list);
// rt_read_getline1.c
int		rt_is_strchr(char *s, char c);
char	*rt_getline(int fd);
char	*rt_eof_check(char **rest, char *line, int read_len);
int		rt_read_line(int fd, char *buffer, char **rest);
int		rt_rl_strchr(const char *s, int c);
// rt_read_getline2.c
char	*rt_strndup(char *buffer, ssize_t len);
char	*rt_line_check(char **rest);
// rt_set_data1.c
int		rt_check_identifier(char *line, t_minirt *list);
int		rt_is_identifier(char *line, char *identifier, int len);
int		rt_set_ambient_lightning(char *line, t_minirt *list);
int		rt_set_camera(char *line, t_minirt *list);
int		rt_set_light(char *line, t_minirt *list);
// rt_set_data2.c
int		rt_set_plain(char *line, t_minirt *list);
int		rt_set_sphere(char *line, t_minirt *list);
int		rt_set_cylinder(char *line, t_minirt *list);
// rt_set_data3.c
int		rt_set_int(char *line, int *i, int *tmp);
int		rt_set_float(char *line, int *i, double *tmp);
int		rt_set_point(char *line, int *i, t_point *tmp);
int		rt_set_color(char *line, int *i, t_color *tmp);
// rt_set_data4.c
int		rt_try_atoi(char *line, int *i, int *j, int *res);
int		rt_try_atof(char *line, int *i, int *j, double *res);
int		rt_check_minus(char c, int *k, int *m);
int		rt_try_atof_before_dot(char *line, int *k, double *res);
int		rt_try_atof_after_dot(char *line, int *k, double *res, double _res);
// rt_set_data5.c
int		rt_add_plane_node(t_minirt *list, t_plane *new);
int		rt_add_sphere_node(t_minirt *list, t_sphere *new);
int		rt_add_cylinder_node(t_minirt *list, t_cylinder *new);
// rt_check_data1.c
int		rt_check_basic_data(t_minirt *list);
int		rt_check_ambient_range(t_ambient ambient);
int		rt_check_camera_range(t_camera camera);
int		rt_check_light_range(t_light light);
// rt_check_data2.c
int		rt_check_sphere_range(t_sphere *sphere);
int		rt_check_plane_range(t_plane *plane);
int		rt_check_cylinder_range(t_cylinder *cylinder);

// rt_utils/
// rt_clear_data.c
int		rt_clear_data(t_minirt *list);
int		rt_clear_plane_node(t_minirt *list, t_plane *tmpp);
int		rt_clear_sphere_node(t_minirt *list, t_sphere *tmps);
int		rt_clear_cylinder_node(t_minirt *list, t_cylinder *tmpc);
// rt_error.c
int		rt_error_msg(char *s, int status);
// rt_print.c
int		rt_print_list_data(t_minirt *list);
int		rt_print_plane_list_data(t_minirt *list, t_plane *tmpp);
int		rt_print_sphere_list_data(t_minirt *list, t_sphere *tmps);
int		rt_print_cylinder_list_data(t_minirt *list, t_cylinder *tmpc);
// rt_rotate_vector.c
t_point	rt_rotate_x(t_point tmp, double theta);
t_point	rt_rotate_y(t_point tmp, double theta);
t_point	rt_rotate_z(t_point tmp, double theta);

// rt_mlx/
// rt_mlx_func.c
int		rt_keyhook(int k, t_mlxlist *list);
int		rt_end(t_mlxlist *list);
// rt_mlx_display.c
int		rt_set_mlx(t_mlxlist *mlx);
int		rt_get_img(t_mlxlist *mlx, t_minirt *list);
int		rt_get_pixel_color(t_minirt *list, int a, int b, int *color);
int		rt_display_mlx(t_mlxlist *mlx, char *name);
void	rt_mlx_pixel_put(t_mlxlist *data, int x, int y, int color);

// rt_cal_utils/
// rt_cal_utils1.c
t_point	normalize_vec(t_point a);
t_point	add_vec(t_point const a, t_point const b);
t_point	multiply_vec(double const mul, t_point const vec);
double	cal_distance(t_point const p1, t_point const p2);
// rt_cal_utils2.c
int		rt_add_light_color(t_color tmp, int *color);
t_ray	rt_get_point_to_light(t_ray obj, t_point light);
t_point	rt_get_vec(t_point const a, t_point const b);
double	rt_inner_prod(t_point const a, t_point const b);
t_point	rt_outer_prod(t_point const *a, t_point const *b);

// rt_calculate/
// rt_ambient.c
int		rt_add_ambient_light(t_ambient *amb, int *c, t_color tmp, t_color obj);
// rt_diffuse.c
t_color	rt_add_diffuse_light(t_light *l, t_ray hit, t_color obj);
double	rt_get_diffuse_light(t_light *l, t_ray hit);
// rt_cal_cam_ray.c
t_point	cal_ray(int *x, int *y, t_camera const *camera);
// rt_cal_object.c
int		cal_object(t_minirt *list, t_ray *cam, t_ray *hit_point);
int		check_object(t_minirt *list, t_ray *ray);
// rt_sphere.c
int		cal_sphere(t_sphere *list, t_ray *cam, t_ray *hit_point, int flag);
int		check_sphere(t_sphere *list, t_ray *cam, int flag);

#endif
