/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:38:39 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/10 15:44:46 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// new node create
// link child and parent (left or right), link2way
// check is pipredir

/**
 * @brief builds ast from lst
 * @returns pointer on first element to execute
 */
// t_ast	*ast_build(t_list **lst)
// {
// 	t_list	*node;
// 	t_ast	*ast;

// 	if (!lst || !*lst)
// 		return (NULL);
// 	node = *lst;
// 	// if (node->type == WORD)
// 	// {
// 	// 	ast = new_ast_node(node->content,)
// 	// }
// 	// while (node && node->type != PIPE)
// 	// node = node->next;
// 	if (node && node->type == PIPE)
// 	{
// 		ast = new_ast_node(node->content, PIPE);
// 		if (!ast)
// 			return (NULL);
// 		ast->left = build_ast(lst);
// 		ast->right = build_ast(&node->next);
// 	}
// 	return (ast);
// }
