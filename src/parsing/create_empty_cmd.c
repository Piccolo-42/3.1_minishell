/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_empty_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:20:31 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/10 11:02:09 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//&& node->prev
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
			if (!has_cmd)
			{
				node = insert_empty_cmd(node);
				if (!node)
					return (0);
			}	
			has_cmd = 0;
		}
		node = node->next;
	}
	return (1);
}

t_list	*insert_empty_cmd(t_list *node)
{
	t_list	*new;

	new = new_node("", CMD);
	if (!new)
		return (error_handler(
				"ast: new_node: memory allocation failed", 1), NULL);
	new->prev = node ;
	new->next = node->next ;
	node->next = new;
	return (new);
}

// int	insert_empty_cmd(t_list *prev_node)
// {
// 	t_list	*new;
// 	t_list	*next_node;

// 	ft_putendl_fd("INSERT", 2);
// 	new = new_node("", CMD);
// 	if (!new)
// 		return (error_handler(
// 				"ast: new_node: memory allocation failed", 1), 0);
// 	if (prev_node)
// 		next_node = prev_node->next ;
// 	else
// 		next_node = NULL;
// 	new->prev = prev_node;
// 	new->next = next_node;
// 	if (next_node)
// 		next_node->prev = new;
// 	if (prev_node)
// 		prev_node->next = new;
// 	ft_putendl_fd("INSERT END", 2);
// 	return (1);
// }
