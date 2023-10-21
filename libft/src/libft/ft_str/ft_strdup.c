/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:25:02 by lliu              #+#    #+#             */
/*   Updated: 2022/11/03 14:29:07 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*temp;
	char	*dst;

	temp = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	dst = temp;
	while (*s1)
		*temp++ = *s1++;
	*temp = '\0';
	return (dst);
}
