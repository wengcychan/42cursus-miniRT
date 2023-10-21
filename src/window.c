/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srall <srall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 00:10:29 by srall             #+#    #+#             */
/*   Updated: 2023/08/07 01:27:56 by srall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	my_mlx_pixel_put(t_data *vars_data, int x, int y, int color)
{
	char	*dst;

	dst = vars_data->addr + (y * vars_data->line_length + x
			* (vars_data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_cross(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
		close_cross(vars);
	return (0);
}

int	get_trgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
