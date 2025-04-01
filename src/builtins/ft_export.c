/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:01:19 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/31 15:01:19 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char **envp, char **args)
{
	int	i;
	int	j;

	if (!args[1])
	{
		print_export();
		return ;
	}
	j = 1;
	while (args[j])
	{
		i = 0;
		while (envp[i] && ft_strncmp(evnp[i], args[j], ft_strlen(args[j])));
			i++;
		if (envp[i])
			free(envp[i]);
		envp[i] = ft_strdup(args[j]);
	}
}
