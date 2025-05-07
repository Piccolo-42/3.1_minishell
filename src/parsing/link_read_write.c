/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_read_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:38:39 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/06 17:31:56 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	removes redirs from main list, 
 * 			attaches them on read/write branch of cmd
 */
int	link_redirs_to_cmd(t_list **lst)
{
	t_list	*cmd;
	t_list	*node;
	t_list	*next;

	cmd = next_cmd(lst);
	if (!cmd)
		return (0);
	node = *lst;
	while (node && node->type != PIPE)
	{
		next = node->next;
		if (is_redir(node->type))
		{
			if (node == *lst)
				*lst = (*lst)->next;
			next = process_redirs(cmd, node);
		}
		node = next;
	}
	if (node && node->type == PIPE)
		link_redirs_to_cmd(&(node->next));
	return (1);
}

t_list	*next_cmd(t_list **lst)
{
	t_list	*node;

	node = *lst;
	while (node)
	{
		if (node->type == CMD)
			return (node);
		node = node->next;
	}
	return (NULL);
}

t_list	*process_redirs_bis(t_list *next_node, t_list *redir)
{
	t_list	*file_node;
	t_list	*after_file;

	file_node = next_node;
	after_file = file_node->next;
	if (file_node->prev)
		file_node->prev->next = file_node->next;
	if (file_node->next)
		file_node->next->prev = file_node->prev;
	file_node->prev = redir;
	file_node->next = NULL;
	redir->next = file_node;
	return (after_file);
}

t_list	*process_redirs(t_list *cmd, t_list *redir)
{
	t_list	**redir_list;
	t_list	*next_node;

	next_node = redir->next;
	if (redir->prev)
		redir->prev->next = redir->next;
	if (redir->next)
		redir->next->prev = redir->prev;
	// ft_printf("%t\n", redir->type);
	if (redir->type == REDIR_IN || redir->type == HEREDOC)
		redir_list = &(cmd->read);
	else
		redir_list = &(cmd->write);
	redir->next = *redir_list;
	redir->prev = NULL;
	if (*redir_list)
		(*redir_list)->prev = redir;
	*redir_list = redir;
	if (next_node && (next_node->type == FIL
			|| next_node->type == ARG || next_node->type == WORD))
		process_redirs_bis(next_node, redir);
	return (next_node);
}

/**
 * @brief (OLD, not in use) 
 * links cmd's and pipe's read/write branches when no redirs
 */
void	link_cmd_and_pipes(t_list **lst)
{
	t_list	*node;

	node = *lst;
	while (node)
	{
		if (node->type == PIPE)
		{
			if (!node->prev && !node->next)
				return ;
			if (!((node->prev)->write))
			{
				(node->prev)->write = node;
				node->read = node->prev;
			}
			if (!((node->next)->read))
			{
				(node->next)->read = node;
				node->write = node->next;
			}
		}
		node = node->next;
	}
	return ;
}

//review
// t_list	*process_redirs(t_list *cmd, t_list *redir)
// {
// 	t_list	**redir_list;
// 	t_list	*next_node;
// 	t_list	*file_node;
// 	t_list	*after_file;
//     next_node = redir->next;
//     if (redir->prev)
//         redir->prev->next = redir->next;
//     if (redir->next)
//         redir->next->prev = redir->prev;
//     if (redir->type == REDIR_IN || redir->type == HEREDOC)
//         redir_list = &(cmd->read);
//     else
//         redir_list = &(cmd->write);
//     redir->next = *redir_list;
//     redir->prev = NULL;
//     if (*redir_list)
//         (*redir_list)->prev = redir;
//     *redir_list = redir;
//     if (next_node && (next_node->type == FIL
//		 || next_node->type == ARG || next_node->type == WORD))
//     {
//         file_node = next_node;
//         after_file = file_node->next;
//         if (file_node->prev)
//             file_node->prev->next = file_node->next;
//         if (file_node->next)
//             file_node->next->prev = file_node->prev;
//         file_node->prev = redir;
//         file_node->next = NULL;
//         redir->next = file_node;
//         return (after_file);
//     }
//     return (next_node);
// }