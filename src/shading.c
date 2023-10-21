/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srall <srall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 00:26:51 by srall             #+#    #+#             */
/*   Updated: 2023/08/07 00:31:00 by srall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	get_ambient(t_ambient *ambient, t_object *obj)
{
	t_vec3	ambient_color;

	ambient_color = multiply_scalar_vec(hadamard_product_vec(ambient->color,
				obj->color), ambient->ratio / 255);
	return (get_trgb(ambient_color.x * SCALE_AMBIENT, ambient_color.y
			* SCALE_AMBIENT, ambient_color.z * SCALE_AMBIENT));
}

static int	get_diffuse(t_light *light, t_intersect intersect)
{
	t_vec3	diffuse_color;

	diffuse_color = multiply_scalar_vec(intersect.obj->color, fmax(0,
				dot_vec(intersect.light_ray, intersect.surface_normal))
			* light->ratio);
	return (get_trgb(diffuse_color.x * SCALE_DIFFUSE, diffuse_color.y
			* SCALE_DIFFUSE, diffuse_color.z * SCALE_DIFFUSE));
}

static int	get_specular(t_light *light, t_intersect intersect)
{
	t_vec3	reflect_vec;
	t_vec3	v_vec;
	t_vec3	specular_color;

	reflect_vec = subtract_vec(multiply_scalar_vec(intersect.surface_normal, 2
				* dot_vec(intersect.surface_normal, intersect.light_ray)),
			intersect.light_ray);
	reflect_vec = subtract_vec(multiply_scalar_vec(intersect.surface_normal, 2
				* dot_vec(intersect.surface_normal, intersect.light_ray)),
			intersect.light_ray);
	v_vec = multiply_scalar_vec(intersect.incident_ray, -1);
	specular_color = multiply_scalar_vec(light->color, SPEC_COEFFICIENT
			* pow(fmax(0, dot_vec(reflect_vec, v_vec)), SPEC_SHININESS)
			* light->ratio);
	return (get_trgb(specular_color.x * SCALE_SPECULAR, specular_color.y
			* SCALE_SPECULAR, specular_color.z * SCALE_SPECULAR));
}

int	get_shading_color(t_scene *scene, t_intersect intersect)
{
	return (get_ambient(scene->ambient, intersect.obj)
		+ get_diffuse(scene->light, intersect) + get_specular(scene->light,
			intersect));
}
