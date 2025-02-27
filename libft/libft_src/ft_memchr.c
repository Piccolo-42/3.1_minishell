/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:12:30 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/14 19:07:16 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief mem[i] = c ? for n bytes
 * @return mem + i || 0 if !
 */
void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *) str;
	while (i < n)
	{
		if (ptr[i] == (char) c)
			return ((void *)(str + i));
		i++;
	}
	return (0);
}
