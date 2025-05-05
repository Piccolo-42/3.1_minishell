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

	if (!src)
		ft_strdup("");
	srclen = ft_strlen(src) + 1;
	dest = malloc(srclen * sizeof(char));
	if (!dest)
		return (0);
	ft_strlcpy(dest, src, srclen);
	return (dest);
}

char	**ft_strdup_double_add_n_free_old(char **str, int n)
{
	char	**dest;
	int		i;
	int		len;

	len = ft_strlen_double(str);
	dest = ft_calloc((len + n + 1), sizeof(char *));
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dest[i] = ft_strdup(str[i]);
		i++;
	}
	ft_free_double(str);
	return (dest);
}
