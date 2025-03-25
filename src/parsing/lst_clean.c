/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:37:30 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/25 15:19:35 by sravizza         ###   ########.fr       */
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

	if (!lst || !*lst)
		return ;
	node = *lst;
	cmd = NULL;
	while (node)
	{
		if (is_redir(node->type))
			assign_redir_and_file(node);
		else if (node->type == WORD && process_cmd_and_args(&cmd, &node))
			continue ;
		else if (node->type == PIPE)
			cmd = NULL;
		node = node->next;
	}
	return ;
}

/**
 * @brief WORD = CMD || ARG ;  cmd->content[1+] = args ; cmd->next = non_arg
 * @return 1 if arg(s) ;  0 if !arg
 */
int	process_cmd_and_args(t_list **cmd, t_list **node)
{
	t_list	*next;

	assign_cmd_or_arg(cmd, *node);
	if (*cmd && (*node)->type == ARG)
	{
		add_arg(*cmd, (*node)->content[0]);
		next = (*node)->next;
		remove_node(cmd, node);
		*node = next;
		return (1);
	}
	return (0);
}

/**
 * @brief if !cmd, WORD = CMD, else WORD = ARG
 */
void	assign_cmd_or_arg(t_list **cmd, t_list *node)
{
	if (!(*cmd))
	{
		node->type = CMD;
		*cmd = node;
		return ;
	}
	node->type = ARG;
	return ;
}
