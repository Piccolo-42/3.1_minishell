/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:14:45 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/19 16:31:49 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	all_paths = ft_split(data->envp[i] + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		temp = ft_strjoin(all_paths[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	free_all(all_paths);
	return (NULL);
}
