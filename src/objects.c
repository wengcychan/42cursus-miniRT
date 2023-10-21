/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srall <srall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 00:05:25 by srall             #+#    #+#             */
/*   Updated: 2023/08/07 01:27:34 by srall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	get_sphere_intersection(t_object *sphere, t_vec3 ray, t_vec3 ray_origin)
{
	double	b;
	double	c;
	t_vec3	origin_to_sphere_center;

	origin_to_sphere_center = create_vec(ray_origin, sphere->center);
	b = 2 * dot_vec(ray, origin_to_sphere_center);
	c = dot_vec(origin_to_sphere_center, origin_to_sphere_center)
		- pow(sphere->diameter / 2, 2);
	return (solve_quadratic_equation(1, b, c));
}

double	get_plane_intersection(t_object *plane, t_vec3 ray, t_vec3 ray_origin)
{
	double	dist;

	dist = dot_vec(create_vec(plane->center, ray_origin), plane->vec_norm)
		/ dot_vec(ray, plane->vec_norm);
	if (dist > 0)
		return (dist);
	return (false);
}

static double	get_cy_base_top_intersection(t_object *cy, t_vec3 ray, int sign,
		t_vec3 ray_origin)
{
	t_object	obj;
	double		dist;

	obj.center = add_vec(cy->center, multiply_scalar_vec(cy->vec_norm,
				cy->height / 2 * sign));
	obj.vec_norm = cy->vec_norm;
	dist = get_plane_intersection(&obj, ray, ray_origin);
	if (dist > 0)
	{
		if (vec_length(create_vec(add_vec(ray_origin, multiply_scalar_vec(ray,
							dist)), obj.center)) > cy->diameter / 2)
			dist = 0;
	}
	return (dist);
}

static double	get_min_dist(double top_dist, double base_dist,
		double surface_dist)
{
	double	min_dist;

	min_dist = INT_MAX;
	if (top_dist > 0 && top_dist < min_dist)
		min_dist = top_dist;
	if (base_dist > 0 && base_dist < min_dist)
		min_dist = base_dist;
	if (surface_dist > 0 && surface_dist < min_dist)
		min_dist = surface_dist;
	if (min_dist == INT_MAX)
		min_dist = 0;
	return (min_dist);
}

double	get_cylinder_intersection(t_object *cy, t_vec3 ray, t_vec3 ray_origin)
{
	t_vec3	vec1;
	t_vec3	vec2;
	double	top_dist;
	double	base_dist;
	double	surface_dist;

	vec1 = cross_vec(ray, cy->vec_norm);
	vec2 = cross_vec(create_vec(ray_origin, cy->center), cy->vec_norm);
	surface_dist = solve_quadratic_equation(pow(vec_length(vec1), 2), 2
			* dot_vec(vec1, vec2), pow(vec_length(vec2), 2)
			- pow(cy->diameter / 2, 2));
	if (surface_dist > 0)
	{
		if (sqrt(pow(cy->diameter / 2, 2) + pow(cy->height / 2,
					2)) <= vec_length(create_vec(add_vec(ray_origin,
						multiply_scalar_vec(ray, surface_dist)), cy->center)))
			surface_dist = 0;
	}
	top_dist = get_cy_base_top_intersection(cy, ray, 1, ray_origin);
	base_dist = get_cy_base_top_intersection(cy, ray, -1, ray_origin);
	return (get_min_dist(top_dist, base_dist, surface_dist));
}
