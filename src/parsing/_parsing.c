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
 * empty cmd end of list if extra space
 */
/** ToDo
 * make interactive and gnl mode, with test file and diff file
 * 
 * update and call free(lst)
 * 
 * error if wrong syntax:
 * no cmd
 * (after pipe)
 * redir w/o file
 * access files and cmds
 * ->error management
 */

/**
 * @brief creates t_list and t_ast
 * @return pointer on the first ast node
 */
t_list	*parsing(char *input)
{
	t_list	*lst;
	t_list	*ast;

	ast = NULL;
	lst = NULL;
	lst = make_lst(input);
	ast = ast_build(&lst);
	return (ast);
}
