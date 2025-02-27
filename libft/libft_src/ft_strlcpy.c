/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:54:14 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/09 14:44:51 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief dst = src for n bytes. 
 * @return strlen(src);
 * @warning check: strlen(dst) >= strlen(src) || >= n
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (ft_strlen(src));
	while (src[i] && (i < n - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (ft_strlen(src));
}
