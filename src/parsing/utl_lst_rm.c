/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_lst_rm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:14:29 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/01 10:28:52 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	// t_list	*node;
	t_list	*next;

	if (!lst || !*lst)
		return ;
	// node = *lst;
	next = NULL;
	while (*lst)
	{
		next = (*lst)->next;
		free_lst_read(*lst);
		free_lst_write(*lst);
		free_double((*lst)->content);
		free(*lst);
		(*lst) = NULL;
		// ft_free((void **)(&node));
		(*lst) = next;
	}
	*lst = NULL;
	return ;
}

void	free_lst_read(t_list *node)
{
	t_list	*temp;
	t_list	*next;

	if(!node || !node->read)
		return ;

	temp = node->read;
	if (is_redir(temp->type))
	{
		while (temp)
		{
			next = temp->next;
			free_double(temp->content);
			free(temp);
			temp = next;
		}
	}
	node->read = NULL;
}

void	free_lst_write(t_list *node)
{
	t_list	*temp;
	t_list	*next;

	temp = node->write;
	if (temp && is_redir(temp->type))
	{
		while (temp)
		{
			next = temp->next;
			free_double(temp->content);
			free(temp);
			temp = next;
		}
	}
	node->write = NULL;
}
