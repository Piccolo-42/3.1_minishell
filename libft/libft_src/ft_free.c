/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 09:46:17 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/02 11:44:17 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_double(char **str)
{
	int	i;

	if (!str || !*str)
		return ;
	i = 0;
	while (str[i])
	{
		ft_free(&(str[i]));
		i++;
	}
	free(str);
	return ;
}

void	ft_free_ptr(void **ptr)
{
	if (!ptr || !*ptr)
		return ;
	free(*ptr);
	*ptr = NULL;
}

void	ft_free(char **str)
{
	if (!str || !*str)
		return ;
	free(*str);
	*str = NULL;
}
