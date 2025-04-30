/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:37:30 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/30 17:37:36 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief removes nodes with type RM (solitary quotes) and empty nodes
 */
void	remove_type_rm(t_list **lst)
{
	t_list	*node;

	if (!lst || !*lst)
		return ;
	node = *lst;
	while (node)
	{
		if (node->type == RM || !(*node->content))
			remove_node(lst, &node);
		else
			node = node->next;
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
				dest = ft_strtrim(node->content[0], "\"");
			else if (node->subtype == SNG_Q)
				dest = ft_strtrim(node->content[0], "\'");
			free(node->content[0]);
			node->content[0] = dest;
			dest = NULL;
		}
		else if (node->type == ENV)
			update_env(node);
		node = node->next;
	}
	return ;
}

/**
 * @brief  reassign type to WORD and subtype to ENV
 */
void	update_env(t_list *node)
{
	node->type = WORD;
	node->subtype = ENV;
}


void	check_syntax(t_list **lst)
{
	t_list *node;
	int		cmd;

	cmd = 0;
	node = *lst;
	while (node)
	{
		if (node->type == CMD && cmd == 1)
		{
			//error
			printf("wrong syntax, tooo many cmd\n");
			break ;
		}
		else if (node->type == CMD && cmd == 0)
			cmd = 1;
		else if (node->type == PIPE && cmd == 0)
		{
			//error
			printf("wrong syntax, missing cmd\n");
			break ;
		}
		else if (node->type == PIPE && cmd == 1)
			cmd = 0;
		node = node->next;
	}
}
