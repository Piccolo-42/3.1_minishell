/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:55:24 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/02 17:10:19 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_list *node)
{
	int	i;

	if (!node || !node->content)
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
