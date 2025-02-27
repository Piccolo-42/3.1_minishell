/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:58:14 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/10 13:52:49 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief use memmove instead
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*pdst;
	char	*psrc;

	if (!dst && !src)
		return (dst);
	i = 0;
	pdst = (char *) dst;
	psrc = (char *) src;
	while (i < n)
	{
		*(pdst + i) = *(psrc + i);
		i++;
	}
	return (dst);
}
/*
int	main()
{
	char src[10] = "42";
	char dst[10] = "ecole";
	ft_memcpy(dst, src, 7);
	printf("%s",dst);
	return (0);
}*/