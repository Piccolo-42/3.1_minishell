/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:59:39 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/09 14:20:30 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief reverse searches c in str (strart from end)
 * @return position of 1st encounter or 0 if none
 */
char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (char) c)
			return ((char *)str + i);
		i--;
	}
	return (0);
}
