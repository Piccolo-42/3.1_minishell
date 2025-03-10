/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:11:42 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/05 13:33:50 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ToDo
// 
// assign ast

t_ast	*parsing(char *input)
{
	t_list	*lst;
	t_ast	*ast;

	lst = NULL;
	lst = tokenisation(input);
	prt_lst(lst);
	ast = ast_build(&lst);
	free_lst(&lst);
	print_ast_basic(ast, 0);
	// ft_printf("\n\n\n");
	// print_ast_graphic(ast, 0, 0);
	return (ast);
}
