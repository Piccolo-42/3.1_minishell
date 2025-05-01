/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:55:24 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/01 16:37:01 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_list *node)
{
	int	i;

	if (!node)
		return (-1);
	i = 1;
	while (node->content[i])
		i++;
	return (i - 1);
}

int	ft_varlen(char *name)
{
	int	i;

	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	return (i);
}
