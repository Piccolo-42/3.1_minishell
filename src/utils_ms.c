/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:31:32 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/01 16:56:55 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//no +1 because we are removing the varaible _=./minishell (if strcmp)
char	**copy_envp(char **envp)
{
	char	**dest;
	int		i;

	i = ft_strlen_double(envp);
	dest = malloc(sizeof(char *) * (i));
	if (!dest)
		return (NULL);
	dest[i] = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "_=", 2))
			dest[i] = ft_strdup(envp[i]);
		i++;
	}
	return (dest);
}
