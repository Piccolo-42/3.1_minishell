/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:26:52 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/01 16:32:46 by sravizza         ###   ########.fr       */
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
			node->content[0] = dblq_replace_env(data, node->content[0]);
		node = node->next;
	}
}

char *replace_env(t_data *data, char *str)
{
	int		i;
	int 	size;
	int		env_size;
	char	*env;

	if (!str)
		return (strdup(""));
	size = ft_strlen(str) - 1;
	i = 0;
	while(data->envp[i])
	{
		env = ft_strchr(data->envp[i], '=');
		if (env)
		{
			env_size = ft_strlen(data->envp[i]) - ft_strlen(env); 
			if (env_size == size && !ft_strncmp(data->envp[i], str + 1, size))
				break ;
		}
		i++;
	}
	free(str);
	if (!data->envp[i])
		return (ft_strdup(""));
	return (ft_strdup(ft_strchr(data->envp[i], '=') + 1));
}

char	*dblq_replace_env(t_data *data, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			str = split_union(str, i, data);
			if (!str)
				return (NULL);
		}
		else
			i++;
	}
	return (str);
}

void	ft_print(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_printf(">%s<\n", str[i]);
		i++;
	}
}

char	*split_union(char *str, int var_start, t_data *data)
{
	char	**temp;
	char	*dest;
	int		i;

	temp = double_null(4);
	if (!temp)
		return (NULL);
	temp[0] = ft_substr(str, 0, var_start);
	i = var_start + 1;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	temp[1] = replace_env(data, ft_substr(str, var_start, i - var_start));
	temp[2] = ft_substr(str, i, ft_strlen(str) - i);
	free(str);
	dest = ft_union_simple(temp);
	free_double(temp);
	if (!dest)
		return (NULL);
	return (dest);
}
