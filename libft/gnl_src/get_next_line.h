/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:39:02 by sravizza          #+#    #+#             */
/*   Updated: 2024/11/07 17:03:16 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 420
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft_src/libft.h"

char	*get_next_line(int fd);
// LIBFT_UTILS
//int		ft_strlen(const char *str);
//char	*ft_strchr(const char *str, int c);
//void	ft_bzero(void *str, unsigned int n);
//void	*ft_calloc(unsigned int nel, unsigned int elsize);

#endif