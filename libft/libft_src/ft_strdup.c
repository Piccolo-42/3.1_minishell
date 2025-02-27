/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:41:55 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/08 12:42:11 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @warning malloc
 * @returns cpy
 */
char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	srclen;

	srclen = ft_strlen(src) + 1;
	dest = malloc(srclen * sizeof(char));
	if (!dest)
		return (0);
	ft_strlcpy(dest, src, srclen);
	return (dest);
}
