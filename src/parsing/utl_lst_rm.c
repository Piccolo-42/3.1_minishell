/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_lst_rm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:14:29 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/24 15:25:16 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_node(t_list **lst, t_list **node)
{
	t_list	*remove;
	t_list	*next;

	if (!*node)
		return ;
	remove = *node;
	next = (*node)->next;
	if (remove->prev)
		(remove->prev)->next = next;
	else
		*lst = next;
	if (next)
		next->prev = remove->prev;
	free_double(remove->content);
	free(remove);
	*node = next;
	return ;
}

void	free_lst(t_list **lst)
{
	t_list	*node;
	t_list	*next;

	if (!lst || !*lst)
		return ;
	node = *lst;
	while (node)
	{
		next = node->next;
		free_lst_redir(node);
		free_double(node->content);
		free(node);
		node = next;
	}
	*lst = NULL;
	return ;
}

void	free_lst_redir(t_list *node)
{
	t_list	*temp;
	t_list	*next;

	temp = node->read;
	while (temp && is_redir(temp->type))
	{
		next = temp->next;
		free_double(temp->content);
		free(temp);
		temp = next;
	}
	node->read = NULL;
	temp = node->write;
	while (temp && is_redir(temp->type))
	{
		next = temp->next;
		free_double(temp->content);
		free(temp);
		temp = next;
	}
	node->write = NULL;
}
