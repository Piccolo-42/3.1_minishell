/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:31:32 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/06 17:02:39 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//no +1 because we are removing the varaible _=./minishell (if strcmp)
char	**copy_envp(char **envp)
{
	char	**dest;
	int		i;
	int		d;

	if (!envp || !*envp)
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
	data->has_envp = 1;
	if (!*envp)
		data->has_envp = 0;
	data->envp = copy_envp(envp);
	if (!data->envp)
		return (free(data), NULL);
	data->prt = 1;
	data->input = NULL;
	data->prompt = NULL;
	data->here_doc = 0;
	signal_init(data);
	return (data);
}

char	**empty_envp(void)
{
	char	**dest;
	char	*cwd;

	dest = malloc(sizeof(char *) * 3);
	if (!dest)
		return (NULL);
	dest[0] = ft_strdup("USER=minishell");
	if (!dest[0])
		return (NULL);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	dest[1] = ft_strjoin_free_two("PWD=", cwd);
	if (!dest[1])
		return (NULL);
	dest[2] = NULL;
	// for (int i = 0; dest[i]; i++)
	// 	printf("dest[%d]= %s\n", i, dest[i]);
	return (dest);
}
