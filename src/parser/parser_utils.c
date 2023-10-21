/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 00:11:53 by srall             #+#    #+#             */
/*   Updated: 2023/10/20 15:49:44 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	ft_atod(const char *str)
{
	int		i;
	int		sign;
	double	res;
	int		power;

	i = 0;
	sign = 1;
	res = 0;
	power = 0;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	if (str[i] == '.')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		res = res + (str[i++] - '0') * pow(10, --power);
	if (str[i] != '\0' && str[i] != '\n')
		ft_error("Wrong parameter in .rt file. (ft_atod)\n", 1);
	return (res * sign);
}

t_vec3	split_3d(char *str, bool is_unit_vec)
{
	char	**res;
	int		count;
	t_vec3	vec;

	res = ft_split(str, ',');
	if (!res)
		ft_error("Malloc Failed4.\n", 1);
	count = 0;
	while (res[count])
		count++;
	if (count != 3)
		ft_error("Wrong parameter in .rt file.\n", 1);
	vec = copy_vec3(ft_atod(res[0]), ft_atod(res[1]), ft_atod(res[2]));
	if (is_unit_vec)
		vec = normalize_vec(vec);
	free_char(res);
	return (vec);
}

void	check_num(char *str, int min, int max, bool is_ratio)
{
	if ((ft_atod(str) <= min && !is_ratio) || (ft_atod(str) < min && is_ratio)
		|| ft_atod(str) > max)
		ft_error("Wrong parameter in .rt file. (check_num)\n", 1);
}

void	check_rgb(char *color_rgb)
{
	t_vec3	rgb;

	rgb = split_3d(color_rgb, 0);
	if (rgb.x < 0 || rgb.x > 255 || rgb.y < 0 || rgb.y > 255 || rgb.z < 0
		|| rgb.z > 255)
		ft_error("Wrong rgb parameter in .rt file. (check_rgb)\n", 1);
}

void	check_3d(char *coordinate_point, bool norm_vec)
{
	t_vec3	xyz;

	xyz = split_3d(coordinate_point, 0);
	if (norm_vec && (xyz.x < -1 || xyz.x > 1 || xyz.y < -1 || xyz.y > 1
			|| xyz.z < -1 || xyz.z > 1))
		ft_error("Wrong parameter in .rt file. (check_vector)\n", 1);
	return ;
}
