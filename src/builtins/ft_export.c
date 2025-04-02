/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:01:19 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/01 16:57:40 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_export(char ***envp, char *var)
{
	int		i;

	i = 0;
	while ((*envp)[i] && ft_strncmp((*envp)[i], var, ft_varlen(var)))
		i++;
	if ((*envp)[i])
		free((*envp)[i]);
	if (!(*envp[i]))
	{
		(*envp) = ft_strdup_double_add_n_free_old((*envp), 1);
		if (!(*envp))
			return ; //error
	}
	(*envp)[i] = ft_strdup(var);

	return ;
}

void	ft_export(char ***envp, char **args)
{
	int	i;

	if (!args[1])
	{
		print_export((*envp));
		return ;
	}
	i = 1;
	while (args[i])
		mini_export(envp, args[i++]);
	return ;
}

void	print_export(char **envp)
{
	int		i;
	char	*equal;

	envp = sort_export(envp);
	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			*equal = 0;
			printf("declare -x %s=\"%s\"\n", envp[i], equal + 1);
			*equal = '=';
		}
		else
			printf("declare -x %s\n", envp[i]);
		i++;
	}
	return ;
}

char	**sort_export(char **envp)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while(envp[i])
	{
		j = i + 1;
		while(envp[j])
		{
			if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i])) > 0)
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (envp);
}
