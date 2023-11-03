/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 00:06:53 by srall             #+#    #+#             */
/*   Updated: 2023/10/27 16:52:20 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	generate_ray(t_scene *scene, int i, int j)
{
	t_vec3	pixel_point;
	t_vec3	pixel_coord_camera;

	pixel_coord_camera = copy_vec3(i + 0.5 - scene->resolution[0] / 2,
			scene->resolution[1] / 2 - j - 0.5, -scene->resolution[0]
			/ (2 * tanf(scene->camera->fov / 2 * M_PI / 180)));
	pixel_point = transform_camera_to_world(scene, pixel_coord_camera);
	return (normalize_vec(create_vec(pixel_point, scene->camera->point)));
}

double	get_intersection(t_object *obj, t_vec3 ray, t_vec3 ray_origin)
{
	if (obj->identifier == 's')
		return (get_sphere_intersection(obj, ray, ray_origin));
	else if (obj->identifier == 'p')
		return (get_plane_intersection(obj, ray, ray_origin));
	else if (obj->identifier == 'c')
		return (get_cylinder_intersection(obj, ray, ray_origin));
	else
		return (false);
}

void	get_nearest_obj(t_list *obj_lst, t_scene *scene, t_intersect *intersect)
{
	double	cur_dist;
	double	ray_dist;

	intersect->obj = NULL;
	ray_dist = -1;
	while (obj_lst)
	{
		cur_dist = get_intersection((t_object *)obj_lst->content,
				intersect->incident_ray, scene->camera->point);
		if (cur_dist > 0 && (ray_dist == -1 || ray_dist > cur_dist))
		{
			ray_dist = cur_dist;
			intersect->obj = (t_object *)obj_lst->content;
		}
		obj_lst = obj_lst->next;
	}
	if (!intersect->obj)
		return ;
	intersect->intersect_point = add_vec(scene->camera->point,
			multiply_scalar_vec(intersect->incident_ray, ray_dist));
	return ;
}

void	get_intersect_surface_normal(t_intersect *intersect)
{
	double	root;

	if (intersect->obj->identifier == 's')
		intersect->surface_normal = create_vec(intersect->intersect_point,
				intersect->obj->center);
	else if (intersect->obj->identifier == 'p')
		intersect->surface_normal = intersect->obj->vec_norm;
	else if (intersect->obj->identifier == 'c')
	{
		root = dot_vec(intersect->obj->vec_norm,
				create_vec(intersect->intersect_point, intersect->obj->center));
		if (fabs(root) < intersect->obj->height / 2 - EPSILON)
			intersect->surface_normal = create_vec(intersect->intersect_point,
					add_vec(intersect->obj->center,
						multiply_scalar_vec(intersect->obj->vec_norm, root)));
		else if (root > 0)
			intersect->surface_normal = intersect->obj->vec_norm;
		else if (root)
			intersect->surface_normal
				= multiply_scalar_vec(intersect->obj->vec_norm, -1);
	}
	intersect->surface_normal = normalize_vec(intersect->surface_normal);
	return ;
}

bool	get_light_intersection(t_list *obj_lst, t_scene *scene,
		t_intersect *intersect)
{
	get_intersect_surface_normal(intersect);
	intersect->offset_point = add_vec(intersect->intersect_point,
			multiply_scalar_vec(intersect->surface_normal, EPSILON));
	intersect->light_ray = normalize_vec(create_vec(scene->light->center,
				intersect->offset_point));
	while (obj_lst)
	{
		if (get_intersection((t_object *)obj_lst->content, intersect->light_ray,
				intersect->offset_point) > 0)
			return (true);
		obj_lst = obj_lst->next;
	}
	return (false);
}
