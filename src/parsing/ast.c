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

// t_ast	*build_ast(t_list **lst)
// {
// 	t_list	*plst;
// 	t_ast	*ast;

// 	if (!lst || !*lst)
// 		return (NULL);
// 	plst = *lst;
// 	if (plst->type == WORD)
// 	{
// 		ast = new_ast_node(plst->content,)
// 	}
// 	// while (plst && plst->type != PIPE)
// 	// 	plst = plst->next;
// 	if (plst && plst->type == PIPE)
// 	{
// 		ast = new_ast_node(plst->content, PIPE);
// 		if (!ast)
// 			return (NULL);
// 		ast->left = build_ast(lst);
// 		ast->right = build_ast(&plst->next);
// 	}
// 	return (ast);
// }
