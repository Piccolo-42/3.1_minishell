/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:37:30 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/06 10:54:21 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief removes nodes with type RM (solitary quotes) and empty nodes
 */
int	remove_type_rm(t_list **lst)
{
	t_list	*node;

	if (!lst || !*lst)
		return (0);
	node = *lst;
	while (node)
	{
		if (node->type == RM || !(*node->content))
			remove_node(lst, &node);
		else
			node = node->next;
	}
	return (1);
}

/**
 * @brief removes actual quotes from str, 
 * reassign type to WORD and subtype to SNG_Q or DBL_Q
 */
int	update_quotes_and_env(t_list **lst)
{
	t_list	*node;

	node = *lst;
	while (node)
	{
		if (node->type == DBL_Q || node->type == SNG_Q)
		{
			if (!update_quotes(node))
				return (0);
		}
		else if (node->type == ENV)
			update_env(node);
		node = node->next;
	}
	return (1);
}

int	update_quotes(t_list *node)
{
	char	*dest;

	dest = NULL;
	node->subtype = node->type;
	node->type = WORD;
	if (node->subtype == DBL_Q)
		dest = ft_strtrim(node->content[0], "\"");
	else if (node->subtype == SNG_Q)
		dest = ft_strtrim(node->content[0], "\'");
	if (!dest)
		return (error_handler("ast: quotes: memory allocation failed", 1), 0);
	free(node->content[0]);
	node->content[0] = dest;
	dest = NULL;
	return (1);
}

/**
 * @brief  reassign type to WORD and subtype to ENV
 */
void	update_env(t_list *node)
{
	node->type = WORD;
	node->subtype = ENV;
}

int	check_syntax(t_list **lst)
{
	t_list	*node;
	int		cmd;

	cmd = 0;
	node = *lst;
	while (node)
	{
		if (node->type == CMD && cmd == 1)
			return (error_handler("syntax error", 2), 0);
		else if (node->type == CMD && cmd == 0)
			cmd = 1;
		else if (node->type == PIPE && cmd == 0)
			return (error_handler(
					"syntax error near unexpected token |", 2), 0);
		else if (node->type == PIPE && cmd == 1)
			cmd = 0;
		// else if (is_redir(node->type))
		// 		return (0);
		node = node->next;
	}
	return (1);
}
