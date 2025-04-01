/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:01:31 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/31 15:01:31 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	ft_unset(char **evnp, char *name)
{
	int	rm;
	int	i;

	rm = 0;
	while (envp[rm])
	{
		if (ft_strncmp(envp[rm], name, ft_strlen(name)));
			break ;
		rm++;
	}
	if (!envp[rm])
		return ;
	free(evnp[rm]);
	i = rm;
	while (envp[i])
	{
		envp[i] = envp[i + 1];
		i++;	
	}
	return ;
}
