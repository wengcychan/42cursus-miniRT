/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 00:15:29 by srall             #+#    #+#             */
/*   Updated: 2023/10/27 16:52:45 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	count_ele(char **line)
{
	int	i;

	i = 0;
	while (line[i] && ft_strncmp(line[i], "\n", 2))
		i++;
	return (i);
}

static void	check_scene(char *line, int *count)
{
	char	**line_str;

	line_str = ft_split(line, ' ');
	if (!line_str)
		ft_error("Malloc Failed1.\n", 1);
	free_str(line);
	if (!ft_strncmp(line_str[0], "R", 2) && count_ele(line_str) == 3)
		check_resolution(line_str, &count[R]);
	else if (!ft_strncmp(line_str[0], "BG", 3) && count_ele(line_str) == 2)
		check_background(line_str, &count[BG]);
	else if (!ft_strncmp(line_str[0], "A", 2) && count_ele(line_str) == 3)
		check_ambient(line_str, &count[A]);
	else if (!ft_strncmp(line_str[0], "C", 2) && count_ele(line_str) == 4)
		check_camera(line_str, &count[C]);
	else if (!ft_strncmp(line_str[0], "L", 2) && count_ele(line_str) == 4)
		check_light(line_str, &count[L]);
	else if ((!ft_strncmp(line_str[0], "sp", 3) && count_ele(line_str) == 4)
		|| (!ft_strncmp(line_str[0], "pl", 3) && count_ele(line_str) == 4)
		|| (!ft_strncmp(line_str[0], "cy", 3) && count_ele(line_str) == 6))
		check_object(line_str);
	else
		ft_error("Wrong1 SCENE parameter in .rt file.\n", 1);
	free_char(line_str);
	return ;
}

void	check_file(char *filename)
{
	int		fd;
	char	*line;
	int		count[5];
	t_elem	i;

	i = A;
	while (i <= BG)
		count[i++] = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Open .rt file failed.\n", 1);
	line = get_next_line(fd);
	while (line)
	{
		while (line && !ft_strncmp(line, "\n", 2) && free_str(line))
			line = get_next_line(fd);
		if (!line)
			break ;
		check_scene(line, count);
		line = get_next_line(fd);
	}
	close(fd);
	if (count[A] != 1 || count[C] != 1 || count[L] != 1 || count[R] != 1
		|| count[BG] != 1)
		ft_error("Wrong2 SCENE parameter in .rt file.\n", 1);
}

static void	assign_scene(char *line, t_scene *scene)
{
	char	**line_str;

	line_str = ft_split(line, ' ');
	if (!line_str)
		ft_error("Malloc Failed3.\n", 1);
	free_str(line);
	if (!ft_strncmp(line_str[0], "R", 2))
		init_resolution(line_str, scene);
	else if (!ft_strncmp(line_str[0], "BG", 3))
		init_background(line_str, scene);
	else if (!ft_strncmp(line_str[0], "A", 2))
		init_ambient(line_str, scene);
	else if (!ft_strncmp(line_str[0], "C", 2))
		init_camera(line_str, scene);
	else if (!ft_strncmp(line_str[0], "L", 2))
		init_light(line_str, scene);
	else if (!ft_strncmp(line_str[0], "sp", 3)
		|| !ft_strncmp(line_str[0], "pl", 3)
		|| !ft_strncmp(line_str[0], "cy", 3))
		init_object(line_str, scene);
	free_char(line_str);
	return ;
}

void	init_scene(char *filename, t_scene *scene)
{
	int		fd;
	char	*line;

	scene->ambient = (t_ambient *)ft_calloc(1, sizeof(t_ambient));
	scene->camera = (t_camera *)ft_calloc(1, sizeof(t_camera));
	scene->light = (t_light *)ft_calloc(1, sizeof(t_light));
	scene->obj_lst = NULL;
	if (!scene->ambient || !scene->camera || !scene->light)
		ft_error("Malloc Failed2.\n", 1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Open .rt file failed.\n", 1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		while (line && !ft_strncmp(line, "\n", 2) && free_str(line))
			line = get_next_line(fd);
		if (!line)
			break ;
		assign_scene(line, scene);
		line = get_next_line(fd);
	}
	close(fd);
	return ;
}
