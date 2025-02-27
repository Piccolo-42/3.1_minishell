/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:35:30 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/10 16:06:24 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief str1 = str2 ? for n bytes
 * @return 0 if equal  |  + if str1 > str2  | - <
 */
int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	i = 0;
	ptr1 = (unsigned char *) str1;
	ptr2 = (unsigned char *) str2;
	while ((i < n) && (ptr1[i] == ptr2[i]))
		i++;
	if (i < n)
		return (ptr1[i] - ptr2[i]);
	return (0);
}
