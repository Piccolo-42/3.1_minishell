/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:37:30 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/07 11:05:57 by sravizza         ###   ########.fr       */
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
// /**
//  * @brief removes actual quotes from str, 
//  * reassign type to WORD and subtype to SNG_Q or DBL_Q
//  */
// int	update_quotes_and_env(t_list **lst)
// {
// 	t_list	*node;

// 	node = *lst;
// 	while (node)
// 	{
// 		if (node->type == DBL_Q || node->type == SNG_Q)
// 		{
// 			if (!update_quotes(node))
// 				return (0);
// 		}
// 		else if (node->type == ENV)
// 			update_env(node);
// 		node = node->next;
// 	}
// 	return (1);
// }

//removes the actual quotes from the string("example" -> example)
char	*update_quotes(char *input)
{
	char	*dest;

	if (input[0] == '\"')
		dest = ft_strtrim(input, "\"");
	else if (input[0] == '\'')
		dest = ft_strtrim(input, "\'");
	if (!dest)
		return (error_handler("ast: quotes: memory allocation failed", 1), NULL);
	free(input);
	return (dest);
}

/**
 * @brief  reassign type to WORD and subtype to ENV
 */
void	update_env(t_list *node)
{
	node->type = WORD;
	node->subtype = ENV;
}

//checks for consecutive pipes or pipes as start or finish
int	check_syntax(t_list **lst)
{
	t_list	*node;
	int		not_pipe;

	not_pipe = 0;
	node = *lst;
	while (node)
	{
		if (node->type != PIPE)
			not_pipe = 1;
		else if (node->type == PIPE && (not_pipe == 0 || !node->next))
			return (error_handler(
					"syntax error near unexpected token |", 2), 0);
		else if (node->type == PIPE && not_pipe == 1)
			not_pipe = 0;
		node = node->next;
	}
	return (1);
}
