/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:40:59 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/08 12:41:19 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief malloc + fills with 0;
 * @return str
 * @warning malloc
 */
void	*ft_calloc(size_t nel, size_t elsize)
{
	void	*str;

	str = malloc (nel * elsize);
	if (!str)
		return (0);
	ft_bzero(str, nel * elsize);
	return (str);
}

char	**double_null(int n)
{
	int		i;
	char	**dest;

	dest = malloc(sizeof(char *) * n);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < n)
		dest[i++] = NULL;
	return (dest);
}
