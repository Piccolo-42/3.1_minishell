/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:45:05 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/10 15:17:58 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*new_node(char *content, t_type type)
{
	t_list	*dest;

	dest = malloc(sizeof(t_list));
	if (!dest)
		return (NULL);
	dest->content = ft_strdup(content);
	if (!(dest->content))
		return (NULL);
	dest->type = NONE;
	dest->subtype = NONE;
	if (type != NONE)
		dest->type = type;
	// if (subtype != NONE)
	// 	dest->subtype = subtype;
	dest->next = NULL;
	dest->args = NULL;
	return (dest);
}

void	node_add_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	free_lst(t_list **lst)
{
	t_list	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		free(temp->content);
		free(temp);
	}
	*lst = NULL;
	return ;
}

void	remove_node(t_list **lst, t_list *prev, t_list **current)
{
	t_list	*temp;

	temp = *current;
	*current = (*current)->next;
	if (prev)
		prev->next = *current;
	else
		*lst = *current;
	free(temp->content);
	free(temp);
}
