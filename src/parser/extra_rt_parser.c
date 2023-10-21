/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_rt_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 01:13:28 by srall             #+#    #+#             */
/*   Updated: 2023/10/20 15:46:48 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_resolution(char **line_str, int *count)
{
	check_num(line_str[1], 0, INT_MAX, false);
	check_num(line_str[2], 0, INT_MAX, false);
	if (line_str[3] != 0)
		ft_error("Wrong parameter in .rt file.\n", 1);
	(*count)++;
}

void	check_background(char **line_str, int *count)
{
	check_rgb(line_str[1]);
	if (line_str[2] != 0)
		ft_error("Wrong parameter in .rt file.\n", 1);
	(*count)++;
}

void	init_resolution(char **line_str, t_scene *scene)
{
	scene->resolution[0] = ft_atod(line_str[1]);
	scene->resolution[1] = ft_atod(line_str[2]);
}

void	init_background(char **line_str, t_scene *scene)
{
	scene->bg_color = split_3d(line_str[1], 0);
	return ;
}
