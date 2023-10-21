/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:51:48 by lliu              #+#    #+#             */
/*   Updated: 2022/11/03 14:22:16 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dst1;
	const char	*src1;

	if (!dst && !src)
		return (NULL);
	dst1 = (char *)dst;
	src1 = (const char *)src;
	while (n--)
		*dst1++ = *src1++;
	return (dst);
}
