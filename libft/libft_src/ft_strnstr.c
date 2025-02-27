/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:55:03 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/15 09:53:12 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief searches needle in haystack for n bytes
 * @return pointer on beggining of needle in haystack | 0 if no occurences
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!haystack && !n)
		return (0);
	if (*needle == 0 || needle == haystack)
		return ((char *) haystack);
	while (haystack[i] && i < n)
	{
		j = 0;
		while (haystack[i + j] && haystack[i + j] == needle[j] && i + j < n)
			j++;
		if (j == ft_strlen(needle))
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}
