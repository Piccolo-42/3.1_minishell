/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:24:20 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/14 19:02:16 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief dst = src for n bytes
 * @return dst
 */
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int				i;
	unsigned char	*pdst;
	unsigned char	*psrc;

	if (!dst && !src)
		return (dst);
	if (dst < src)
		return (ft_memcpy(dst, src, n));
	i = n - 1;
	pdst = (unsigned char *) dst;
	psrc = (unsigned char *) src;
	while (i >= 0)
	{
		pdst[i] = psrc[i];
		i--;
	}
	return (dst);
}
