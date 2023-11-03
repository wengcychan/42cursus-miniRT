/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vec1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 00:01:05 by srall             #+#    #+#             */
/*   Updated: 2023/10/27 15:48:06 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	copy_vec3(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec3	create_vec(t_vec3 point_end, t_vec3 point_start)
{
	t_vec3	new_vec;

	new_vec.x = point_end.x - point_start.x;
	new_vec.y = point_end.y - point_start.y;
	new_vec.z = point_end.z - point_start.z;
	return (new_vec);
}

double	vec_length(t_vec3 vec)
{
	return (sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
}

t_vec3	normalize_vec(t_vec3 vec)
{
	t_vec3	unit_vec;
	double	length;

	length = vec_length(vec);
	if (length == 0)
		return (vec);
	unit_vec.x = vec.x / length;
	unit_vec.y = vec.y / length;
	unit_vec.z = vec.z / length;
	return (unit_vec);
}

double	dot_vec(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}
