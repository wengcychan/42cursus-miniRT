/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 00:13:22 by srall             #+#    #+#             */
/*   Updated: 2023/10/19 16:29:59 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_filename(char *filename)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(filename);
	while (i++ < len - 3)
		filename++;
	return (ft_strncmp(filename, ".rt", 4));
}

void	check_ambient(char **line_str, int *count)
{
	check_num(line_str[1], 0, 1, true);
	check_rgb(line_str[2]);
	if (line_str[3] != 0)
		ft_error("Wrong parameter in .rt file.\n", 1);
	(*count)++;
}

void	check_camera(char **line_str, int *count)
{
	check_3d(line_str[1], false);
	check_3d(line_str[2], true);
	check_num(line_str[3], 0, 180, true);
	if (line_str[4] != 0)
		ft_error("Wrong parameter in .rt file.\n", 1);
	(*count)++;
}

void	check_light(char **line_str, int *count)
{
	check_3d(line_str[1], false);
	check_num(line_str[2], 0, 1, true);
	check_rgb(line_str[3]);
	if (line_str[4] != 0)
		ft_error("Wrong parameter in .rt file.\n", 1);
	(*count)++;
}

void	check_object(char **line_str)
{
	check_3d(line_str[1], false);
	if (line_str[0][0] == 's')
		check_num(line_str[2], 0, INT_MAX, false);
	else if (line_str[0][0] == 'p' || line_str[0][0] == 'c')
		check_3d(line_str[2], true);
	if (line_str[0][0] == 's' || line_str[0][0] == 'p')
	{
		check_rgb(line_str[3]);
		if (line_str[4] != 0)
			ft_error("Wrong parameter in .rt file.\n", 1);
	}
	else if (line_str[0][0] == 'c')
	{
		check_num(line_str[3], 0, INT_MAX, false);
		check_num(line_str[4], 0, INT_MAX, false);
		check_rgb(line_str[5]);
		if (line_str[6] != 0)
			ft_error("Wrong parameter in .rt file.\n", 1);
	}
	return ;
}
