/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:11:03 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/10 17:34:42 by sravizza         ###   ########.fr       */
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

typedef enum e_type
{
	PIPE,		// |
	REDIR_IN,	// <
	REDIR_OUT,	// >
	APPEND,		// >>
	HEREDOC,	// <<
	CMD,		// command
	FL,			// file
	ARG,		// arguments and flags
	ENV,		// $ENV
	SNG_Q,		// quotes ''
	DBL_Q,		// quotes ""
	WORD,		// undefined yet
	RM,			// solitary quotes to remove
	NONE,		// default, not assigned yet
}	t_type;

typedef struct s_list
{
	char			*content;
	t_type			type;
	t_type			subtype;
	struct s_list	*next;
	struct s_list	*args;
}	t_list;

typedef struct s_ast
{
	t_type			type;		// Type of node (command, pipe, etc.)
	char			*value;
	t_list			*args;		// Linked list of arguments (for commands)
	struct s_ast	*parent;	// root
	struct s_ast	*left;		// Left child (used for pipes and redirections)
	struct s_ast	*right;		// Right child (used for pipes and redirections)
}	t_ast;

// main

// zgeg
void	prt_lst(t_list *lst);
char	*get_type_name(t_type type);
void	print_ast_basic(t_ast *ast, int level);
void	print_ast_graphic(t_ast *ast, int level, int indent);

// ast
t_ast	*ast_build(t_list **lst);

// parsing
t_ast	*parsing(char *input);

// token
t_list	*tokenisation(char *input);
int		process_token(char *input, t_list **lst);
t_type	get_type(char *input, int *i);
// void	define_words(t_list	**lst);

// utils_ast
t_ast	*new_ast_node(char *value, t_type type);
void	add_args_to_node(t_ast **ast, t_ast *arg);
void	add_child_to_node(t_ast	**ast, t_ast *child, int side);
void	free_ast(t_ast	*ast);

// utils_clean_lst
void	clean_up_lst(t_list **lst);
void	remove_type_rm(t_list **lst);
void	update_quotes(t_list **lst);
void	assign_word_type(t_list **lst);
void	add_args_to_cmd(t_list **lst);
void	unlink_end_of_args(t_list **cmd);

// utils_lst
t_list	*new_node(char *input, t_type type);
void	node_add_back(t_list **lst, t_list *new);
void	free_lst(t_list **lst);
void	clean_up_lst(t_list **lst);
void	remove_node(t_list **lst, t_list *prev, t_list **current);

// utils_pars
int		is_whitespace(char c);
int		is_redir(t_type	type);
// char	*crop_whitespace(char *str, int crop);

// utils_token
t_type	handle_quotes(char *input, int *i);
t_type	handle_redir(char *input, int *i);
t_type	handle_env(char *input, int *i);
t_type	handle_words(char *input, int *i);
t_type	handle_pipe(int	*i);

#endif