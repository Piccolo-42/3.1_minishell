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

/**
 * @brief removes nodes with type RM (solitary quotes)
 */
void	remove_type_rm(t_list **lst)
{
	t_list	*node;

	if (!lst || !*lst)
		return ;
	node = *lst;
	while (node)
	{
		if (node->type == RM)
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
				dest = ft_strtrim(node->content[0],"\"");
			else if (node->subtype == SNG_Q)
				dest = ft_strtrim(node->content[0], "\'");
			free(node->content[0]);
			node->content[0] = dest;
			dest = NULL;
		}
		node = node->next;
	}
	return ;
}

/**
 * @brief assigns types to WORDs: 
 * FL after redir.
 * else CMD, and following words are ARGS 
 */
void	assign_word_type(t_list **lst)
{
	t_list	*node;
	t_list	*cmd;

	if(!lst || !*lst)
		return ;
	node = *lst;
	cmd = NULL;
	while (node)
	{
		if (is_redir(node->type) && (node->next))
			assign_file(&node) ;
		else if (node->type == WORD && process_word(&cmd, &node))
			continue ;
		else if (node->type == PIPE)
			cmd = NULL;
		node = node->next;
	}
	return ;
}
