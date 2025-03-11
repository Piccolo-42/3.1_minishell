/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_clean_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:37:30 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/10 17:49:42 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_up_lst(t_list **lst)
{
	remove_type_rm(lst);
	update_quotes(lst);
	assign_word_type(lst);
	add_args_to_cmd(lst);
	return ;
}

void	remove_type_rm(t_list **lst)
{
	t_list	*current;
	t_list	*prev;

	if (!lst || !*lst)
		return ;
	current = *lst;
	prev = NULL;
	while (current)
	{
		if (current->type == RM)
			remove_node(lst, prev, &current);
		else
		{
			prev = current;
			current = current->next;
		}
	}
	return ;
}

void	update_quotes(t_list **lst)
{
	t_list	*node;
	char	*dest;

	dest = NULL;
	node = *lst;
	while (node)
	{
		if (node->type == DBL_Q || node->type == SNG_Q)
		{
			node->subtype = node->type;
			node->type = WORD;
			if (node->subtype == DBL_Q)
				dest = ft_strtrim(node->content,"\"");
			else if (node->subtype == SNG_Q)
				dest = ft_strtrim(node->content, "\'");
			free(node->content);
			node->content = dest;
			dest = NULL;
		}
		node = node->next;
	}
	return ;
}

void	assign_word_type(t_list **lst)
{
	t_list	*node;

	node = *lst;
	while (node)
	{
		if (is_redir(node->type))
			(node->next)->type = FL;
		if (node->type == WORD)
			add_args_to_cmd(&node);
		node = node->next;
	}
	return ;
}

void	add_args_to_cmd(t_list **node)
{
	t_list	*cmd;
	t_list	*temp;

	// if (!lst || !*lst)
	// 	return ;
	// if ((*lst)->type != WORD)
	// 	return;
	cmd = *node;
	cmd->type = CMD;
	if (!cmd->next)
		return;
	if ((cmd->next)->type != WORD)
		return;
	temp = cmd->next;
	while (temp && temp->type == WORD)
	{
		temp->type = ARG;
		temp = temp->next;			
	}
	cmd->args = cmd->next;
	cmd->next = temp;
	unlink_end_of_args(&cmd);
	return ;
}

void	unlink_end_of_args(t_list **cmd)
{
	t_list	*node;

	if (!cmd || !*cmd)
		return;
	node = (*cmd)->args;
	while(node)
	{
		if ((node->next)->type != ARG)
			break;
		node = node->next;
	}
	node->next = NULL;
	return ;
}
