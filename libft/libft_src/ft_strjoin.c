/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:46:49 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/10 16:49:47 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @warning malloc
 * @return str1 + str2
 */
char	*ft_strjoin(char const *str1, char const *str2)
{
	char	*dest;
	size_t	i;

	if (!str1)
		return (printf("RETURN\n"). ft_strdup(str2));
	dest = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!dest)
		return (0);
	i = 0;
	while (str1[i])
	{
		dest[i] = str1[i];
		i++;
	}
	i = 0;
	while (str2[i])
	{
		dest[ft_strlen(str1) + i] = str2[i];
		i++;
	}
	dest[ft_strlen(str1) + i] = 0;
	return (dest);
}
