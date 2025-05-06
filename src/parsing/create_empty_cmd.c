/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_empty_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:20:31 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/06 14:28:00 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	create_empty_cmd(t_list **lst)
{
	int		has_cmd;
	t_list	*node;

	has_cmd = 0;
	node = *lst;
	while (node)
	{
		if (node->type == CMD)
			has_cmd = 1;
		if (node->type == PIPE || !(node->next))
		{
			if (!has_cmd && node->prev && !insert_empty_cmd(node->prev))
				return (0);
			has_cmd = 0;
		}
		node = node->next;
	}
	return (1);
}

int	insert_empty_cmd(t_list *prev_node)
{
	t_list	*new;
	t_list	*next_node;

	new = new_node("", CMD);
	if (!new)
		return (error_handler(
				"ast: new_node: memory allocation failed", 1), 0);
	next_node = prev_node->next ;
	new->prev = prev_node;
	new->next = next_node;
	next_node->prev = new;
	prev_node->next = new;
	return (1);
}
