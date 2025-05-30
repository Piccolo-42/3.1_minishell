/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:26:52 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/10 11:00:51 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief goes through node, expands $ENV, also in "DBLQ"
 */
int	expand_env(t_list **lst, t_data *data)
{
	int		i;
	t_list	*node;

	node = *lst;
	while (node)
	{
		i = 0;
		while (node->content[i])
		{
			if (node->content[i][0] == '$')
				node->content[i] = replace_env(data, node->content[i]);
			else if (node->content[i][0] == '\"')
				node->content[i] = dblq_replace_env(data,
						update_quotes(node->content[i]));
			else if (node->content[i][0] == '\'')
				node->content[i] = update_quotes(node->content[i]);
			if (!node->content[i])
				return (error_handler("Error expanding variables", 1), 0);
			i++;
		}
		node = node->next;
	}
	return (1);
}

/**
 * @brief looks for "input" in data->envp
 * @param input format: "$NAME"
 * @return !input || !value  ? "" : value
 * @returns (or global exit code of $?)
 */
char	*replace_env(t_data *data, char *input)
{
	int		i;
	int		size;
	int		env_size;
	char	*env;

	if (!input)
		return (strdup(""));
	if (!ft_strncmp(input, "$?", 2))
		return (ft_free(&input), ft_itoa(g_exit_code));
	size = ft_strlen(input) - 1;
	i = 0;
	while (data->envp[i])
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
	if (!data->envp[i])
		return (ft_free(&input), ft_strdup(""));
	return (ft_free(&input), ft_strdup((ft_strchr(data->envp[i], '=') + 1)));
}

//expands all $ENV in "double quotes" node
char	*dblq_replace_env(t_data *data, char *content)
{
	int		i;

	if (!content)
		return (NULL);
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
	while (input[i] && (ft_isalnum(input[i])
			|| input[i] == '?' || input[i] == '_'))
		i++;
	temp[1] = replace_env(data, ft_substr(input, var_start, i - var_start));
	temp[2] = ft_substr(input, i, ft_strlen(input) - i);
	ft_free(&input);
	if (!temp[0] || !temp[1] || !temp[2])
		return (NULL);
	dest = ft_union_simple(temp);
	ft_free_double(temp);
	if (!dest)
		return (NULL);
	return (dest);
}
