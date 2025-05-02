/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:31:32 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/02 13:35:10 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//no +1 because we are removing the varaible _=./minishell (if strcmp)
char	**copy_envp(char **envp)
{
	char	**dest;
	int		i;
	int		d;

	i = ft_strlen_double(envp);
	dest = malloc(sizeof(char *) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	d = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "_=", 2))
			dest[d++] = ft_strdup(envp[i]);
		i++;
	}
	dest[d] = NULL;
	return (dest);
}

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->envp = copy_envp(envp);
	if (!data->envp)
		return (free(data), NULL);
	data->exit_code = 0;
	data->input = NULL;
	data->prompt = NULL;
	return (data);
}
