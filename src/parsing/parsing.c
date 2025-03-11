/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:11:42 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/10 16:14:09 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** FIX
 * empty cmd end of list
 */
/** ToDo
 * make interactive and gnl mode, with test file and diff file
 * multiple redirections
 * redirection between cmd and arg
 * error if wrong syntax
 * build ast
 */

/**
 * @brief creates t_list and t_ast
 * @return pointer on the first ast node
 */
t_ast	*parsing(char *input)
{
	t_list	*lst;
	t_ast	*ast;

	ast = NULL;
	lst = NULL;
	lst = make_lst(input);
	prt_lst(lst);
	// ast = ast_build(&lst);
	// free_lst(&lst);
	// print_ast_basic(ast, 0);
	// ft_printf("\n\n\n");
	// print_ast_graphic(ast, 0, 0);
	return (ast);
}
