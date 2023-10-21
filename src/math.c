/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srall <srall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 00:00:54 by srall             #+#    #+#             */
/*   Updated: 2023/08/07 01:27:20 by srall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	solve_quadratic_equation(double a, double b, double c)
{
	double	delta;
	double	root_effective;

	delta = b * b - 4 * a * c;
	if (delta > 0)
	{
		root_effective = fmin((-b - sqrt(delta)) / (2 * a),
				(-b + sqrt(delta)) / (2 * a));
		if (root_effective > 0)
			return (root_effective);
	}
	return (false);
}

t_vec3	transform_camera_to_world(t_scene *scene, t_vec3 p)
{
	t_coord	cam_coord;
	t_vec3	translate;

	cam_coord.w = scene->camera->vec_norm;
	cam_coord.u = cross_vec(copy_vec3(0, 1, 0), cam_coord.w);
	if (cam_coord.u.x == 0 && cam_coord.u.y == 0 && cam_coord.u.z == 0)
		cam_coord.u.x = 1;
	cam_coord.v = cross_vec(cam_coord.w, cam_coord.u);
	translate = create_vec(scene->camera->point, copy_vec3(0, 0, 0));
	return (copy_vec3(p.x * cam_coord.u.x + p.y * cam_coord.v.x + p.z
			* cam_coord.w.x + translate.x, p.x * cam_coord.u.y + p.y
			* cam_coord.v.y + p.z * cam_coord.w.y + translate.y, p.x
			* cam_coord.u.z + p.y * cam_coord.v.z + p.z * cam_coord.w.z
			+ translate.z));
}
