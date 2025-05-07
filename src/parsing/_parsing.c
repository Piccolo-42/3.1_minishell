/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:11:42 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/07 11:50:12 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** FIX
 *
 */
/** ToDo
 * make interactive and gnl mode, with test file and diff file
 *
 * error if wrong syntax:
 * ->error management
 * 
 */

/**
 * @brief creates token list and transforms it into (simili-) ast
 * @return pointer on the first cmd node
 */
t_list	*parsing(t_data *data)
{
	t_list	*lst;

	lst = token_lst(data->input);
	if (!remove_type_rm(&lst)
		|| !assign_word_type(&lst, data)
		|| !expand_env(&lst, data)
		|| !check_syntax(&lst)
		|| !create_empty_cmd(&lst)
		|| !link_redirs_to_cmd(&lst))
	{
		free_lst(&lst);
		return (NULL);
	}
	return (lst);
}

/**
 * @brief creates t_list, skips whitespaces in input
 * @returns pointer on first node of lst
 */
t_list	*token_lst(char *input)
{
	t_list	*lst;
	int		i;
	int		token_len;

	lst = NULL;
	i = 0;
	while (input[i])
	{
		while (is_whitespace(input[i]))
			i++;
		token_len = create_token(input + i, &lst);
		if (token_len == -1)
			return (free_lst(&lst), NULL);
		i += token_len;
	}
	return (lst);
}
