/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:04:09 by srall             #+#    #+#             */
/*   Updated: 2023/07/14 21:59:46 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_gettempstr(int num_read, int fd, char *buff, char *staticstr)
{
	char	*temp;

	if (!staticstr)
	{
		temp = (char *)ft_calloc_gnl(1, 1);
		if (!temp)
			return (NULL);
	}
	while (num_read == BUFFER_SIZE && !ft_strchr(buff, '\n'))
	{
		num_read = read(fd, buff, BUFFER_SIZE);
		if (num_read < 0)
			return (NULL);
		buff[num_read] = '\0';
		if (!staticstr)
			temp = ft_joint(temp, buff);
		else
			temp = ft_joint(staticstr, buff);
		staticstr = NULL;
		if (!temp)
			return (NULL);
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	int			num_read;
	static char	*staticstr;
	char		*temp;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buff = (char *)ft_calloc_gnl((BUFFER_SIZE + 1), sizeof(char));
	if (!buff)
		return (NULL);
	num_read = BUFFER_SIZE;
	temp = ft_gettempstr(num_read, fd, buff, staticstr);
	free(buff);
	if (!temp)
		return (NULL);
	staticstr = ft_staticstr(temp);
	return (ft_line(temp));
}
