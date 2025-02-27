/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:29:54 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/08 13:46:34 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief ft_putstr_fd + newline
 */
void	ft_putendl_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &(str[i]), 1);
		i++;
	}
	write(fd, "\n", 1);
	return ;
}
/*
{
	ft_putendl_fd("je suis fatigué", 1);
}
*/