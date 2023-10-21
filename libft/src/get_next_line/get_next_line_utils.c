/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srall <srall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:05:42 by srall             #+#    #+#             */
/*   Updated: 2023/08/07 01:22:57 by srall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c && !*s)
		return (((char *)s));
	return (NULL);
}

void	*ft_calloc_gnl(size_t count, size_t size)
{
	size_t	i;
	char	*addr;

	if (!count || !size)
		return (ft_calloc_gnl(1, 1));
	if (count * size / size != count)
		return (NULL);
	addr = malloc((count + 1) * size);
	if (!addr)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		addr[i] = 0;
		i++;
	}
	addr[i] = '\0';
	return (addr);
}

char	*ft_joint(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	i = 0;
	j = 0;
	len = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	temp = (char *)ft_calloc_gnl((i + j + 1), sizeof(char));
	if (!temp)
		return (NULL);
	i = 0;
	len = 0;
	while (s1[i])
		temp[len++] = s1[i++];
	j = 0;
	while (s2[j])
		temp[len++] = s2[j++];
	free(s1);
	temp[len] = '\0';
	return (temp);
}

char	*ft_line(char *temp)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	j = 0;
	if (!temp[i])
	{
		free(temp);
		return (NULL);
	}
	while (temp[i] != '\n' && temp[i])
		i++;
	dst = (char *)ft_calloc_gnl((i + 2), sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (temp[i] && temp[i] != '\n')
		dst[j++] = temp[i++];
	if (temp[i] == '\n')
		dst[j++] = '\n';
	dst[j] = '\0';
	free(temp);
	return (dst);
}

char	*ft_staticstr(char *temp)
{
	int		i;
	int		j;
	char	*staticstr;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (!temp[i])
		return (NULL);
	j = 0;
	while (temp[j])
		j++;
	staticstr = ft_calloc_gnl((j - i + 1), sizeof(char));
	if (!staticstr)
		return (NULL);
	if (temp[i] == '\n')
		i++;
	j = 0;
	while (temp[i])
		staticstr[j++] = temp[i++];
	staticstr[j] = '\0';
	return (staticstr);
}
