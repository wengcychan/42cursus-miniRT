/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srall <srall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 23:59:11 by srall             #+#    #+#             */
/*   Updated: 2023/08/07 01:16:59 by srall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	ray_tracing(t_scene *scene, t_data *data)
{
	int			i;
	int			j;
	t_intersect	intersect;

	i = -1;
	while (++i < scene->resolution[0])
	{
		j = -1;
		while (++j < scene->resolution[1])
		{
			intersect.incident_ray = generate_ray(scene, i, j);
			get_nearest_obj(scene->obj_lst, scene, &intersect);
			if (intersect.obj)
			{
				if (!get_light_intersection(scene->obj_lst, scene, &intersect))
					my_mlx_pixel_put(data, i, j, get_shading_color(scene,
							intersect));
				else
					my_mlx_pixel_put(data, i, j, 0x000000);
			}
			else
				my_mlx_pixel_put(data, i, j, get_trgb(scene->bg_color.x,
						scene->bg_color.y, scene->bg_color.z));
		}
	}
}

int	main(int ac, char **av)
{
	t_scene		scene;
	t_vars		vars;

	if (ac < 2 || check_filename(av[1]))
		ft_error("Input Error: ./minirt <description.rt>\n", 1);
	check_file(av[1]);
	init_scene(av[1], &scene);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, scene.resolution[0],
			scene.resolution[1], "MINIRT");
	vars.img.img = mlx_new_image(vars.mlx, scene.resolution[0],
			scene.resolution[1]);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel,
			&vars.img.line_length, &vars.img.endian);
	ray_tracing(&scene, &vars.img);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_hook(vars.win, 17, 0, close_cross, &vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
	free_scene(&scene);
	return (0);
}
