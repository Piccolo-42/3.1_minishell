/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:11:42 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/25 16:59:55 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** FIX
 * 
 */
/** ToDo
 * make interactive and gnl mode, with test file and diff file
 * 
 * 
 * error if wrong syntax:
 * no cmd
 * (after pipe)
 * ->error management
 */

/**
 * @brief creates token list and transforms it into (simili-) ast
 * @return pointer on the first ast node
 */
t_list	*parsing(char *input)
{
	t_list	*lst;
	t_list	*ast;

	ast = NULL;
	lst = NULL;
	lst = token_lst(input);
	ast = ast_build(&lst);
	return (ast);
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
	clean_up_lst(&lst);
	return (lst);
}

/**
 * @brief removes quotes, reassigns types and sublinks args
 */
void	clean_up_lst(t_list **lst)
{
	remove_type_rm(lst);
	update_quotes(lst);
	assign_word_type(lst);
	return ;
}

t_list	*ast_build(t_list **lst)
{
	link_redirs_to_cmd(lst);
	link_cmd_and_pipes(lst);
	check_syntax(lst);
	return (*lst);
}

void	check_syntax(t_list **lst)
{
	t_list *node;
	int		cmd;

	cmd = 0;
	node = *lst;
	while (node)
	{
		if (node->type == CMD && cmd == 1)
		{
			//error
			printf("wrong syntax, tooo many cmd\n");
			break ;
		}
		else if (node->type == CMD && cmd == 0)
			cmd = 1;
		else if (node->type == PIPE && cmd == 0)
		{
			//error
			printf("wrong syntax, missing cmd\n");
			break ;
		}
		else if (node->type == PIPE && cmd == 1)
			cmd = 0;
		node = node->next;
	}
}
