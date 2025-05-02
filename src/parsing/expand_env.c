/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:26:52 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/01 22:11:01 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * @brief goes through lst, expands subtype $ENV and envs in "DBLQ"
 */
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
		if (!node->content[0])
			return ; //error
		node = node->next;
	}
}
/**
 * @brief looks for "input" in data->envp 
 * @param input format: "$NAME"
 * @return !input || !value  ? "" : value
 */
char *replace_env(t_data *data, char *input)
{
	int		i;
	int 	size;
	int		env_size;
	char	*env;

	if (!input)
		return (strdup(""));
	size = ft_strlen(input) - 1;
	i = 0;
	while(data->envp[i])
	{
		env = ft_strchr(data->envp[i], '=');
		if (env)
		{
			env_size = ft_strlen(data->envp[i]) - ft_strlen(env); 
			if (env_size == size && !ft_strncmp(data->envp[i], input + 1, size))
				break ;
		}
		i++;
	}
	free(input);
	if (!data->envp[i])
		return (ft_strdup(""));
	return (ft_strdup(ft_strchr(data->envp[i], '=') + 1));
}

//expands all $ENV in "double quotes" node
char	*dblq_replace_env(t_data *data, char *content)
{
	int		i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			content = split_union(content, i, data);
			if (!content)
				return (NULL);
		}
		else
			i++;
	}
	return (content);
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

/**
 * @brief expands one variable
 * @param input old_content
 * @param var_start index of '$'
 * @returns new_content with one expanded varaible
 */
char	*split_union(char *input, int var_start, t_data *data)
{
	char	**temp;
	char	*dest;
	int		i;

	temp = double_null(4);
	if (!temp)
		return (NULL);
	temp[0] = ft_substr(input, 0, var_start);
	i = var_start + 1;
	while (input[i] && ft_isalnum(input[i]))
		i++;
	temp[1] = replace_env(data, ft_substr(input, var_start, i - var_start));
	temp[2] = ft_substr(input, i, ft_strlen(input) - i);
	free(input);
	dest = ft_union_simple(temp);
	free_double(temp);
	if (!dest)
		return (NULL);
	return (dest);
}
