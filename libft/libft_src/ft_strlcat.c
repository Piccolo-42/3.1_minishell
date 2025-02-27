/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:13:40 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/10 14:45:40 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief appends src to dst for n bytes (!strdup)
 * @param n length of new dest
 * @return strlen(src) + min(n, dstlen), if RV >= n: truncation
 */
size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	isrc;
	size_t	dstlen;

	dstlen = ft_strlen(dst);
	isrc = 0;
	while (src[isrc] && ((dstlen + isrc + 1) < n))
	{
		dst[dstlen + isrc] = src[isrc];
		isrc++;
	}
	if (isrc < n)
		dst[dstlen + isrc] = 0;
	if (n <= dstlen)
		return (ft_strlen(src) + n);
	else
		return (ft_strlen(src) + dstlen);
}
/*
int main ()
{
	char dest[11] = "PP";
    printf("%ld\n", ft_strlcat(dest, "", 25));
    printf("%s\n", dest);
	
}
*/