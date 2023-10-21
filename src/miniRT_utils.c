/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srall <srall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 00:05:18 by srall             #+#    #+#             */
/*   Updated: 2023/08/07 01:27:30 by srall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_error(char *msg, int S_EXIT)
{
	write(2, RED "Error\n" RESET, 15);
	ft_putstr_fd(msg, 2);
	if (S_EXIT)
		exit(1);
	return ;
}

int	free_str(char *str)
{
	free(str);
	str = NULL;
	return (1);
}

void	free_char(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != NULL)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	create_lst(t_list **lst, void *content)
{
	t_list	*node;

	node = ft_lstnew(content);
	if (!node)
		ft_error("Malloc failed.\n", 1);
	ft_lstadd_back(lst, node);
}

void	free_scene(t_scene *scene)
{
	free(scene->ambient);
	free(scene->camera);
	free(scene->light);
	free(scene->resolution);
	ft_lstfree(scene->obj_lst);
	return ;
}
