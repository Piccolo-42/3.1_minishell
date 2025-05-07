/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:14:45 by emurillo          #+#    #+#             */
/*   Updated: 2025/05/07 09:48:17 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

//locate PATH in environment
char	*pathfinder(char *cmd, t_data *data)
{
	char	**all_paths;
	char	*path;
	char	*temp;
	int		i;

	if (!data->envp)
		return (NULL);
	i = 0;
	while (data->envp[i] && ft_strnstr(data->envp[i], "PATH=", 5) == 0)
		i++;
	if (!data->envp[i])
		return (NULL);
	all_paths = ft_split(data->envp[i] + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		temp = ft_strjoin(all_paths[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, F_OK) == 0)
			return (free_split(all_paths), path);
		free(path);
		i++;
	}
	return (free_split(all_paths), NULL);
}
