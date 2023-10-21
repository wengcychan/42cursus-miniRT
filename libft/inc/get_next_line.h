/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliu <lliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:03:59 by srall             #+#    #+#             */
/*   Updated: 2023/07/14 21:59:01 by lliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*ft_strchr(const char *s, int c);
void	*ft_calloc_gnl(size_t count, size_t size);
char	*ft_joint(char *s1, char *s2);
char	*ft_line(char *str);
char	*ft_staticstr(char *str);

char	*get_next_line(int fd);

#endif
