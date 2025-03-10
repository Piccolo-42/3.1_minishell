/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zgeg.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:15:58 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/10 17:43:14 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /**
//  * @brief call function w level = 0;
//  */
// void	print_ast_basic(t_ast *ast, int level)
// {
//     if (!ast)
//         return;
    
//     // Indentation for tree structure visualization
//     for (int i = 0; i < level; i++)
//         printf("  ");

//     // Print the current node's type and value
//     printf("Type: %d, Value: %s\n", ast->type, ast->value ? ast->value : "NULL");

//     // Recursively print left and right children
//     print_ast_basic(ast->left, level + 1);
//     print_ast_basic(ast->right, level + 1);
// }

// /**
//  * @brief call function w level & indent = 0
//  */
// void print_ast_graphic(t_ast *ast, int level, int indent)
// {
//     if (!ast)
//         return;

//     // Indentation for tree visualization
//     for (int i = 0; i < indent; i++)
//         printf(" ");

//     // Print the current node's type and value
//     if (ast->value)
//         printf("(%s: %s)\n", (ast->type == CMD) ? "CMD" : (ast->type == PIPE) ? "PIPE" : "REDIR", ast->value);
//     else
//         printf("(%s: NULL)\n", (ast->type == CMD) ? "CMD" : (ast->type == PIPE) ? "PIPE" : "REDIR");

//     // Print left child
//     if (ast->left)
//     {
//         for (int i = 0; i < indent; i++)
//             printf(" ");
//         printf("├── Left ->\n");
//         print_ast_graphic(ast->left, level + 1, indent + 4);
//     }

//     // Print right child
//     if (ast->right)
//     {
//         for (int i = 0; i < indent; i++)
//             printf(" ");
//         printf("└── Right ->\n");
//         print_ast_graphic(ast->right, level + 1, indent + 4);
//     }

//     // Print args
//     if (ast->args)
//     {
//         for (int i = 0; i < indent; i++)
//             printf(" ");
//         printf("Args ->\n");
//         print_ast_graphic(ast->args, level + 1, indent + 4);
//     }
// }

void	prt_lst(t_list *lst)
{
	int		i;
	t_list	*arg;

	if (!lst)
		return ;
	ft_printf("\n");
	i = 0;
	while (lst)
	{
		if (lst->content)
			ft_printf("%d: %s", i, lst->content);
		else
			ft_printf("no content");
		ft_printf(" , (%s)", get_type_name(lst->type));
		if(lst->subtype == SNG_Q || lst->subtype == DBL_Q)
			ft_printf(", (%s)", get_type_name(lst->subtype));
		if (lst->args)
		{
			ft_printf(", args-> ");
			arg = lst->args;
			while (arg)
			{
				ft_printf("(%s) ", arg->content);
				arg = arg->next;
			}
			arg = NULL;
		}
		ft_printf("\n");
		i++;
		lst = lst->next;
	}
	return ;
}

char	*get_type_name(t_type type)
{
	if (type == FL)
		return ("FL");
	if (type == CMD)
		return ("CMD");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	if (type == REDIR_OUT)
		return ("REDIR_OUT");
	if (type == APPEND)
		return ("APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == ARG)
		return ("ARG");
	if (type == ENV)
		return ("ENV");
	if (type == SNG_Q)
		return ("SNG_Q");
	if (type == DBL_Q)
		return ("DBL_Q");
	if (type == WORD)
		return ("WORD");
	if (type == NONE)
		return ("NONE");
	if (type == RM)
		return ("RM"); 
	return ("UNKNOWN");
}
