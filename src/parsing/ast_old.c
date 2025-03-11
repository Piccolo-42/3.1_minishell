/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:24:06 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/08 21:24:06 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ast_build(t_list **lst)
{
	t_ast	*ast;
	t_list	*tmp;

	if (!lst || !*lst)
		return (NULL);
	ast = NULL;
	tmp = *lst;
	if (tmp->type == WORD)
	{
		ast = new_ast_node(tmp->content, tmp->type);
		*lst = (*lst)->next;
		return (ast);
	}
	if (tmp->type == PIPE)
	{
		*lst = (*lst)->next;
		ast = new_ast_node("|", PIPE);
		ast->left = ast_build(lst); // Left side of the pipe
		ast->right = ast_build(lst); // Right side of the pipe
		return (ast);	
	}
	if (is_redir(tmp->type))
	{
		ast = new_ast_node(tmp->content, tmp->type);
		*lst = (*lst)->next;
		ast->right = ast_build(lst); // Recursively process the file or argument after redirection
		return (ast);
	}
	ast = new_ast_node(tmp->content, CMD); // Treat as a command node
	*lst = (*lst)->next; // Move to the next token
	while (*lst && (*lst)->type == WORD)
	{
		t_ast *arg_node = ast_build(lst);  // Recursive call for arguments
		add_args_to_node(&ast, arg_node);  // Add the argument to the node's args list
	}
	return (ast);
}

