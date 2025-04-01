/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:01:31 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/01 17:29:50 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char ***envp, char **args)
{
	int	a;

	a = 1;
	while (args[a])
	{
		mini_unset(envp, args[a]);
		a++;
	}
	return ;
}

void	mini_unset(char ***envp, char *name)
{
	int	rm;
	int	i;

	rm = 0;
	while ((*envp)[rm] && ft_strncmp((*envp)[rm], name, ft_strlen(name)))
		rm++;
	if (!(*envp)[rm])
		return ;
	free((*envp)[rm]);
	i = rm;
	while (envp[i])
	{
		(*envp)[i] = (*envp)[i + 1];
		i++;
	}
	return ;
}
