/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:31:32 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/05 17:25:29 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//no +1 because we are removing the varaible _=./minishell (if strcmp)
char	**copy_envp(char **envp)
{
	char	**dest;
	int		i;
	int		d;

	if (!envp)
		return (empty_envp());
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
	data->prt = 1;
	data->input = NULL;
	data->prompt = NULL;
	signal_init(data);
	return (data);
}

char	**empty_envp(void)
{
	char	**dest;

	dest = malloc(sizeof(char *) * 1);
	if (!dest)
		return (NULL);
	dest[0] = NULL;
	return (dest);
}
