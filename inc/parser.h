/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:45:02 by wchan             #+#    #+#             */
/*   Updated: 2023/10/20 15:43:13 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "miniRT.h"

typedef enum e_elem
{
	A,
	C,
	L,
	R,
	BG,
}				t_elem;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct s_ambient
{
	double		ratio;
	t_vec3		color;
}				t_ambient;

typedef struct s_camera
{
	t_vec3		point;
	t_vec3		vec_norm;
	uint8_t		fov;
}				t_camera;

typedef struct s_light
{
	t_vec3		center;
	double		ratio;
	t_vec3		color;
}				t_light;

typedef struct s_object
{
	char		identifier;
	t_vec3		center;
	t_vec3		vec_norm;
	double		diameter;
	double		height;
	t_vec3		color;
}				t_object;

// scene initialization
typedef struct s_scene
{
	int			resolution[2];
	t_vec3		bg_color;
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_list		*obj_lst;
}				t_scene;

// parser.c
int		check_filename(char *filename);
void	check_file(char *filename);
void	init_scene(char *filename, t_scene *scene);

// parser_utils.c
double	ft_atod(const char *str);
t_vec3	split_3d(char *str, bool is_unit_vec);
void	check_num(char *str, int min, int max, bool is_ratio);
void	check_rgb(char *color_rgb);
void	check_3d(char *coordinate_point, bool norm_vec);

// parser_checker.c
void	check_ambient(char **line_str, int *count);
void	check_camera(char **line_str, int *count);
void	check_light(char **line_str, int *count);
void	check_object(char **line_str);

// parser_init.c
void	init_ambient(char **line_str, t_scene *scene);
void	init_camera(char **line_str, t_scene *scene);
void	init_light(char **line_str, t_scene *scene);
void	init_object(char **line_str, t_scene *scene);

// extra_rt_parser.c
void	check_resolution(char **line_str, int *count);
void	check_background(char **line_str, int *count);
void	init_resolution(char **line_str, t_scene *scene);
void	init_background(char **line_str, t_scene *scene);

#endif
