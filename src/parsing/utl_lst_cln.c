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

/**
 * @brief removes nodes with type RM (solitary quotes)
 */
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

/**
 * @brief removes actual quotes from str, 
 * reassign type to WORD and subtype to SNG_Q or DBL_Q
 */
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

/**
 * @brief assigns types to WORDs: 
 * FL after redir.
 * else CMD, and following words are ARGS 
 */
void	assign_word_type(t_list **lst)
{
	t_list	*node;

	if(!lst || !*lst)
		return ;
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

/**
 * @brief assigns CMD to words that are not FL, ARG to following words. 
 * @brief \n CMD's linked list of args are now pointed to by cmd->args 
 */
void	add_args_to_cmd(t_list **node)
{
	t_list	*cmd;
	t_list	*temp;

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

/**
 * @brief unlinks the rest of the lst (not args) from the last arg
 */
void	unlink_end_of_args(t_list **cmd)
{
	t_list	*arg;

	if (!(*cmd)->args)
		return ;
	arg = (*cmd)->args;
	while(arg)
	{
		if (arg->next && (arg->next)->type != ARG)
			break ;
		arg = arg->next;
	}
	if (arg)
		arg->next = NULL;
	return ;
}
