/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:26:52 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/30 18:31:51 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_env(t_list **lst, t_data *data)
{
	t_list *node;

	node = *lst;
	while (node)
	{
		if (node->subtype == ENV)
			node->content[0] = replace_env(data, node->content[0]);
		else if (node->subtype == DBL_Q)
			node->content[0] = dblq_replace_env(data, content[0]);
		node = node->next;
	}
}

char	*dblq_replace_env(t_data *data, char *str)
{
	char	**temp;
	char	*dest;
	int		i;
	int		j;

	temp = ft_split(str, ' ');
	if (!temp)
		return (NULL);
	free(str);
	while (temp[i])
	{
		j = 0;
		while (is_whitespace(temp[i][j]))
			j++;
		if (temp[i][j] == '$')
			temp[i] = ft_strjoin(
				ft_substr(temp[i], 0, j), replace_env(data, temp[i]));
		i++
	}
	dest = ft_union(temp, ' ');
	if (!dest)
		return (NULL);
	free_double(temp);
	return (dest);
}

char *replace_env(t_data *data, char *str)
{
	int	i;
	int size;
	int end;

	size = ft_strlen(str + 1);
	i = 0;
	while(data->envp[i])
	{
		if (ft_strncmp(envp[i], var, size))
			break ;
		i++;
	}
	free(str);
	if (!data->envp[i])
		return ("");
	end = ft_strlen(envp[i] + size + 1);
	free(str);
	return (ft_substr(envp[i], size, end));
}
