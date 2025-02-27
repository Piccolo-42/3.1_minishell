/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:06:51 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/09 14:54:15 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @warning malloc
 */
char	*ft_strmapi(char const*str, char (*ft)(unsigned int, char))
{
	int		i;
	char	*dest;

	dest = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dest)
		return (0);
	i = 0;
	while (str[i])
	{
		dest[i] = (*ft)(i, (str[i]));
		i++;
	}
	dest[i] = 0;
	return (dest);
}
