/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:44:49 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/08 12:37:46 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief str = c for n bytes
 */
void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(str + i) = (char) c;
		i++;
	}
	return (str);
}
