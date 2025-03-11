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

t_ast	*new_ast_node(char *value, t_type type)
{
	t_ast	*dest;

	dest = malloc(sizeof(t_ast));
	if (!dest)
		return (NULL);
	dest->value = ft_strdup(value);
	if (!(dest->value))
    {
        free(dest);
        return (NULL);
    }
	dest->type = type;
	dest->left = NULL;
	dest->right = NULL;
	dest->args = NULL;
	return (dest);
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

