/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 00:12:06 by srall             #+#    #+#             */
/*   Updated: 2023/10/20 15:43:55 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_ambient(char **line_str, t_scene *scene)
{
	scene->ambient->ratio = ft_atod(line_str[1]);
	scene->ambient->color = split_3d(line_str[2], 0);
	return ;
}

void	init_camera(char **line_str, t_scene *scene)
{
	scene->camera->point = split_3d(line_str[1], 0);
	scene->camera->vec_norm = split_3d(line_str[2], 1);
	scene->camera->fov = ft_atod(line_str[3]);
	return ;
}

void	init_light(char **line_str, t_scene *scene)
{
	scene->light->center = split_3d(line_str[1], 0);
	scene->light->ratio = ft_atod(line_str[2]);
	scene->light->color = split_3d(line_str[3], 0);
	return ;
}

void	init_object(char **line_str, t_scene *scene)
{
	t_object	*object;

	object = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!object)
		ft_error("Malloc Failed7.\n", 1);
	object->identifier = line_str[0][0];
	object->center = split_3d(line_str[1], 0);
	if (object->identifier == 's')
		object->diameter = ft_atod(line_str[2]);
	else if (object->identifier == 'p' || object->identifier == 'c')
		object->vec_norm = split_3d(line_str[2], 1);
	if (object->identifier == 's' || object->identifier == 'p')
		object->color = split_3d(line_str[3], 0);
	else if (object->identifier == 'c')
	{
		object->diameter = ft_atod(line_str[3]);
		object->height = ft_atod(line_str[4]);
		object->color = split_3d(line_str[5], 0);
	}
	create_lst(&scene->obj_lst, object);
	return ;
}
