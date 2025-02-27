/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:12:44 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/10 17:46:57 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *str, void (*ft)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		(*ft)(i, str + i);
		i++;
	}
	return ;
}
