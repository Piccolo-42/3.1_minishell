/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:47:46 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/04 11:07:13 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief assigns types to WORDs:
 * FL after redir.
 * else CMD, and following words are ARGS
 */
void	assign_word_type(t_list **lst)
{
	t_list	*node;
	t_list	*cmd;

	if (!lst || !*lst)
		return ;
	node = *lst;
	cmd = NULL;
	while (node)
	{
		if (is_redir(node->type))
			assign_redir_and_file(node);
		else if (node->type == WORD && process_cmd_and_args(&cmd, &node))
			continue ;
		else if (node->type == PIPE)
			cmd = NULL;
		node = node->next;
	}
	return ;
}

/**
 * @brief WORD = CMD || ARG ;  cmd->content[1+] = args ; cmd->next = non_arg
 * @return 1 if arg(s) ;  0 if !arg
 */
int	process_cmd_and_args(t_list **cmd, t_list **node)
{
	t_list	*next;

	assign_cmd_or_arg(cmd, *node);
	if (*cmd && (*node)->type == ARG)
	{
		add_arg(*cmd, (*node)->content[0]);
		next = (*node)->next;
		remove_node(cmd, node);
		*node = next;
		return (1);
	}
	return (0);
}

/**
 * @brief if !cmd, WORD = CMD, else WORD = ARG
 */
void	assign_cmd_or_arg(t_list **cmd, t_list *node)
{
	if (!(*cmd))
	{
		node->type = CMD;
		*cmd = node;
		return ;
	}
	node->type = ARG;
	return ;
}
