/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:41:49 by wchan             #+#    #+#             */
/*   Updated: 2023/10/19 14:44:56 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// system headers
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>

// 42 headers
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include "define.h"

// miniRT headers
# include "parser.h"

# define EPSILON 0.00001

# define SCALE_AMBIENT 0.33
# define SCALE_DIFFUSE 0.33
# define SCALE_SPECULAR 0.34
# define SPEC_COEFFICIENT 1
# define SPEC_SHININESS 10
// Note: initialize all the structs

// minilibx
typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_data		img;
}				t_vars;

// for ray tracing

typedef struct s_coord
{
	t_vec3		u;
	t_vec3		v;
	t_vec3		w;
}				t_coord;

typedef struct s_intersect
{
	t_object	*obj;
	t_vec3		intersect_point;
	t_vec3		surface_normal;
	t_vec3		offset_point;
	t_vec3		incident_ray;
	t_vec3		light_ray;
	t_vec3		reflection_ray;
}				t_intersect;
//ray_tracing.c
t_vec3		generate_ray(t_scene *scene, int i, int j);
double		get_intersection(t_object *obj, t_vec3 ray, t_vec3 ray_origin);
void		get_nearest_obj(t_list *obj_lst,
				t_scene *scene, t_intersect *intersect);
void		get_intersect_surface_normal(t_intersect *intersect);
bool		get_light_intersection(t_list *obj_lst,
				t_scene *scene, t_intersect *intersect);

//math_vec.c
t_vec3		copy_vec3(double x, double y, double z);
t_vec3		create_vec(t_vec3 point_end, t_vec3 point_start);
double		vec_length(t_vec3 vec);
t_vec3		normalize_vec(t_vec3 vec);
double		dot_vec(t_vec3 vec1, t_vec3 vec2);
t_vec3		hadamard_product_vec(t_vec3 vec1, t_vec3 vec2);
t_vec3		cross_vec(t_vec3 vec1, t_vec3 vec2);
t_vec3		add_vec(t_vec3 vec1, t_vec3 vec2);
t_vec3		subtract_vec(t_vec3 vec1, t_vec3 vec2);
t_vec3		multiply_scalar_vec(t_vec3 vec, double k);

// math
double		solve_quadratic_equation(double a, double b, double c);
t_vec3		transform_camera_to_world(t_scene *scene, t_vec3 p);

// window.c
void		my_mlx_pixel_put(t_data *vars_data, int x, int y, int color);
int			close_cross(t_vars *vars);
int			key_hook(int keycode, t_vars *vars);
int			get_trgb(int r, int g, int b);

// miniRT_utils.c
void		ft_error(char *msg, int S_EXIT);
int			free_str(char *str);
void		free_char(char **str);
void		create_lst(t_list **lst, void *content);
void		free_scene(t_scene *scene);

// objects.c
double		get_sphere_intersection(t_object *sphere,
				t_vec3 ray, t_vec3 ray_origin);
double		get_plane_intersection(t_object *plane,
				t_vec3 ray, t_vec3 ray_origin);
double		get_cylinder_intersection(t_object *cy,
				t_vec3 ray, t_vec3 ray_origin);

// shading.c
int			get_shading_color(t_scene *scene, t_intersect intersect);

#endif
