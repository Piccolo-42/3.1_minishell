/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_union.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:07:59 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/01 15:29:32 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_union(char **str, char c)
{
	char	*dest;
	int		i;
	int		j;
	int		d;
	int		size;

	size = ft_strlen_double_all(str) + ft_strlen_double(str) - 1;
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	d = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
			dest[d++] = str[i][j++];
		if (str[i + 1])
			dest[d++] = c;
		i++;
	}
	dest[d] = 0;
	return (dest);
}

char	*ft_union_simple(char **str)
{
	char	*dest;
	int		i;
	int		j;
	int		d;
	int		size;

	size = ft_strlen_double_all(str);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	d = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
			dest[d++] = str[i][j++];
		i++;
	}
	dest[d] = 0;
	return (dest);
}
