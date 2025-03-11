/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 20:35:03 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/08 20:35:03 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*tokenisation(char *input)
{
	t_list	*lst;
	int	i;

	lst = NULL;
	i = 0;
	while (input[i])
	{
		while (is_whitespace(input[i]))
			i++;
		i += process_token(input + i, &lst);
	}
	clean_up_lst(&lst);
	return (lst);
}

int	process_token(char *input, t_list **lst)
{
	int		i;
	t_type	type;
	char	*token;

	i = 0;
	type = get_type(input, &i);
	token = ft_substr(input, 0, i);
	if (!token)
		return (0);
	node_add_back(lst, new_node(token, type));
	free(token);
	return (i);
}

t_type	get_type(char *input, int *i)
{
	if (input[*i] == '\"' || input[*i] == '\'')
		return (handle_quotes(input, i));
	if (input[*i] == '|')
	{
		(*i)++;
		return (PIPE);
	}
		// return (handle_pipe(i));
	if (input[*i] == '<' || input[*i] == '>')
		return (handle_redir(input, i));
	if (input[*i] == '$')
		return (handle_env(input, i));
	return (handle_words(input, i));
}
