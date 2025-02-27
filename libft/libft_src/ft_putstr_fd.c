/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:29:11 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/08 14:42:29 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief -> ft_putendl_fd = putstr +  \ n
 */
void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &(str[i]), 1);
		i++;
	}
	return ;
}
