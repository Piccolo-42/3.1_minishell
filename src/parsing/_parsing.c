/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:11:42 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/08 16:34:37 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/** FIX
 *
 */
/** ToDo
 * make interactive and gnl mode, with test file and diff file
 *
 * error if wrong syntax:
 * ->error management
 */

/**
 * @brief creates token list and transforms it into (simili-) ast
 * @return pointer on the first cmd node
 */
t_list	*parsing(char *input)
{
	t_list	*lst;

	lst = token_lst(input);
	remove_type_rm(&lst);
	update_quotes(&lst);
	assign_word_type(&lst);
	link_redirs_to_cmd(&lst);
	link_cmd_and_pipes(&lst);
	check_syntax(&lst);
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

	lst = NULL;
	i = 0;
	while (input[i])
	{
		while (is_whitespace(input[i]))
			i++;
		i += create_token(input + i, &lst);
	}
	// clean_up_lst(&lst);
	return (lst);
}
