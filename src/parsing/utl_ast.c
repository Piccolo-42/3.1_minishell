/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:07:32 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/10 15:55:52 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*new_ast_node(t_list *lst)
{
	t_ast	*dest;

	if(!lst)
		return (NULL);
	dest = malloc(sizeof(t_ast));
	if (!dest)
		return (NULL);
	dest->lst = lst;
	dest->args = NULL;
	if (lst->args)
		dest->args = lst->args;
	dest->parent = NULL;
	dest->left = NULL;
	dest->right = NULL;
	return (dest);
}

void	link_children_and_parent(t_ast **left_child, t_ast **parent, t_ast **right_child)
{
	t_ast	*par;
	t_ast	*child;

	if (!parent || !*parent)
		return ;
	par = *parent;
	if (*left_child)
	{
		child = *left_child;
		child->parent = par;
		par->left = child;
	}
	if (*right_child)
	{
		child = *right_child;
		child->parent = par;
		par->right = child;
	}
	return ;
}

// void	add_args_to_node(t_ast **ast, t_ast *arg)
// {
// 	t_ast	*tmp;

// 	if (!*ast)
// 	{
// 		*ast = arg;
// 		return ;
// 	}
// 	tmp = *ast;
// 	while (tmp->args)
// 		tmp = tmp->args;
// 	tmp->args = arg;
// 	return ;
// }

// /**
//  * @param side 0 for left, 1 for right
//  */
// void	add_child_to_node(t_ast	**ast, t_ast *child, int side)
// {
// 	t_ast	*tmp;

// 	if (!*ast)
// 	{
// 		*ast = child;
// 		return ;
// 	}
// 	tmp = *ast;
// 	while ()

// }

// void	free_ast(t_ast	*ast)
// {
// 	if (!ast)
// 		return ;
// 	free_ast(ast->left);
// 	free_ast(ast->right);
// 	free_ast(ast->args);
// 	free(ast->value);
// 	free(ast);
// 	return ;
// }

