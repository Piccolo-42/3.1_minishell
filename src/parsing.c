/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:10:26 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/04 15:40:47 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char *input)
{
	t_list	*lst;
	char	*token;
	int		i;

	i = 0;
	// while (input[i])
	// {
	// 	token = get_token(input, i);
	// 	i++;
	// }

	if (input)
	{
		parsing(get_leftover(input, i, lst));
	}
	else
		prt_lst(lst);
	free(input);
}

char	*get_leftover(char *input, int i, t_list *lst)
{
	char	*token;
	char	*leftover;

	token = get_token(input, i);
	if (!token)
		return (NULL);
	node_add_back(&lst, new_node(token));
	leftover = ft_substr(input, i, ft_strlen(token));
	free(token);
	free(input);
	return (leftover);
}

char	*get_token(char *input, int i)
{
	// char	*token;
	int		start;
	int		len;

	len = 0;
	while (input[i])
	{
		if (input[i] == '\"')
		{
			start = i;
			while (input[i] && input[i] != '\"')
				i++;
			if (input[start] == '\"' && input[i] == '\"')
				return (ft_substr(input, start, i - start));
			else
				i = start++;
		}
		if (input[i] == '\'')
		{
			start = i;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[start] == '\"' && input[i] == '\'')
				return (ft_substr(input, start, i - start));
			else
				i = start++;
		}
		if (input[i] == '<' || input[i] == '>' ||  input [i] == "|")
			return (ft_substr(input, i, 1));
		if (input[i] == '<' && input[i+1] && input[i + 1] == '<')
			return (ft_substr(input, i , 2));
		if (input[i] == '>' && input[i+1] && input[i + 1] == '>')
			return (ft_substr(input, i , 2));
		if (input[i] == '$')
		{
			start = i;
			i++;
			while (input[i] && ft_isalnum(input[i]))
				i++;
			return (ft_substr(input, start, i - start));
		}
		i++;
	}
}
