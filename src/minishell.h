/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:11:03 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/05 14:14:13 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft_src/libft.h"
# include "../libft/gnl_src/get_next_line.h"
# include "../libft/printf_src/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_list
{
	char			*content;
	t_type			*type;
	struct s_list	*next;
}	t_list;

typedef enum e_type {
	CMD,      
	PIPE,		// |
	REDIR_IN,	// <
	REDIR_OUT,	// >
	APPEND,		// >>
	HEREDOC,	// <<
	ARG,		// flags, files
	NONE,		// default, not assigned yet
}	t_type;

typedef struct s_ast {
	t_type         type;   // Type of node (command, pipe, etc.)
	char           *value; // Command name or argument (optional)
	struct s_ast   *left;  // Left child (used for pipes and redirections)
	struct s_ast   *right; // Right child (used for pipes and redirections)
	struct s_ast   *args;  // Linked list of arguments (for commands)
}	t_ast;

//main


//parsing
void	parsing(char *input, t_ast *ast);
void	tokenisation(char *input, t_list **lst);
char	*get_token(char *input);

//utils_lst
t_list	*new_node(char *input);
void	node_add_back(t_list **lst, t_list *new);
void	free_lst(t_list **lst);
// int		ft_lstsize(t_list *lst);
void	prt_lst(t_list *lst);

//utils_ast
t_ast	*new_ast_node(char *value, t_type type);

//utils_pars
int is_whitespace(char c);
int	len_crop(char *input, int len_token);

#endif