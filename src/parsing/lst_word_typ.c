/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_word_typ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 10:27:11 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/15 16:39:19 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * @brief after redir: WORD = FL ;  redir->args = FL ;  redir->next = FL->next
 */
void	assign_file(t_list **redir)
{
	((*redir)->next)->type = FIL;
	add_arg(*redir, (*redir)->next->content[0]);
	remove_node(redir, &(*redir)->next);
}

/**
 * @brief WORD = CMD || ARG ;  cmd->content[1+] = args ; cmd->next = non_arg
 * @return 1 if arg(s) ;  0 if !arg
 */
int	process_word(t_list **cmd, t_list **node)
{
	t_list	*next;

	assign_cmd_and_args(cmd, *node);
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
void	assign_cmd_and_args(t_list **cmd, t_list *node)
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
