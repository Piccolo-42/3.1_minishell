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
	t_list	*plst;
	char	*dest;

	dest = NULL;
	plst = *lst;
	while (plst)
	{
		if (plst->type == DBL_Q || plst->type == SNG_Q)
		{
			plst->subtype = plst->type;
			plst->type = WORD;
			if (plst->subtype == DBL_Q)
				dest = ft_strtrim(plst->content,"\"");
			else if (plst->subtype == SNG_Q)
				dest = ft_strtrim(plst->content, "\'");
			free(plst->content);
			plst->content = dest;
			dest = NULL;
		}
		plst = plst->next;
	}
	return ;
}

void	assign_word_type(t_list **lst)
{
	t_list	*plst;

	plst = *lst;
	while (plst)
	{
		if (is_redir(plst->type))
		{
			// plst = plst->next;
			(plst->next)->type = FL;
		}
		if (plst->type == WORD)
			add_args_to_cmd(&plst);
		plst = plst->next;
	}
	return ;
}

void	add_args_to_cmd(t_list **lst)
{
	t_list	*cmd;
	t_list	*not_arg;

	if (!lst || !*lst)
		return ;
	if ((*lst)->type != WORD)
		return;
	cmd = *lst;
	cmd->type = CMD;
	if (!cmd->next)
		return;
	if ((cmd->next)->type != WORD)
		return;
	not_arg = cmd->next;
	while (not_arg && not_arg->type == WORD)
	{
		not_arg->type = ARG;
		not_arg = not_arg->next;			
	}
	cmd->args = cmd->next;
	cmd->next = not_arg;
	unlink_end_of_args(&cmd);
	return ;
}

void	unlink_end_of_args(t_list **cmd)
{
	t_list	*plst;

	if (!cmd || !*cmd)
		return;
	plst = (*cmd)->args;
	while(plst)
	{
		if ((plst->next)->type != ARG)
			break;
		plst = plst->next;
	}
	plst->next = NULL;
	return ;
}
