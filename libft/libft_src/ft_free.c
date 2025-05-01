/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 09:46:17 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/01 11:40:55 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_double(char **str)
{
	int	i;

	if (!str || !*str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return ;
}

void	ft_free_double(char **str)
{
	int	i;

	if (!str || !*str)
		return ;
	i = 0;
	while (str[i])
	{
		ft_safe_free((void **) &(str[i]));
		i++;
	}
	free(str);
	return ;
}

void	ft_free(char *str)
{
	if (!str)
		return;
	free(str);
}

void	ft_safe_free(void **ptr)
{
	if (!(*ptr))
	{
		(*ptr) = NULL;
		return;
	}
	free((*ptr));
	return ;
}
