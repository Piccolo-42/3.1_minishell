/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:47:46 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/06 17:17:07 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief assigns types to WORDs:
 * FL after redir. checks files
 * else CMD, and following words are ARGS
 */
int	assign_word_type(t_list **lst, t_data *data)
{
	t_list	*node;
	t_list	*cmd;
	int		check;

	if (!lst || !*lst)
		return (0);
	node = *lst;
	cmd = NULL;
	while (node)
	{
		if (is_redir(node->type) && !assign_redir_and_file(node, data))
			return (0);
		else if (node->type == WORD)
		{
			check = process_cmd_and_args(&cmd, &node);
			if (check == 1)
				continue ;
			else if (check == -1)
				return (0);
		}
		else if (node->type == PIPE)
			cmd = NULL;
		node = node->next;
	}
	return (1);
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
		if (!add_arg(*cmd, (*node)->content[0]))
			return (-1);
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
