/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:27:26 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/10 15:32:43 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief compares str1 and str2 for size n
 * @return 0 if equal | + if str1>str2 | - < 
 */
int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (str1[i] && (i < n) && (str1[i] == str2[i]))
		i++;
	if (i < n)
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	return (0);
}
