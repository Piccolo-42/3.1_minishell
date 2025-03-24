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
	FIL,		// file
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
	char			**content;
	t_type			type;
	t_type			subtype;
	struct s_list	*prev;
	struct s_list	*next;
	struct s_list	*read;
	struct s_list	*write;
}	t_list;

// typedef struct s_ast
// {
// 	t_list			*lst;
// 	t_list			*args;		// Linked list of arguments (for commands)
// 	struct s_ast	*parent;	// root
// 	struct s_ast	*left;		// Left child (used for pipes and redirections)
// 	struct s_ast	*right;		// Right child (used for pipes and redirections)
// }	t_ast;

// main


// parsing (main)
t_list	*parsing(char *input);

// ast (Abstract Syntax Tree build)
t_list	*ast_build(t_list **lst);
t_list *process_redirs(t_list *cmd, t_list *redir);
t_list	*next_cmd(t_list **lst);
void	link_redirs_to_cmd(t_list **lst);
void	link_cmd_and_pipes(t_list **lst);


// lst_ (t_list with tokens)
t_list	*make_lst(char *input);
int		process_token(char *input, t_list **lst);
t_type	get_type(char *input, int *i);
void	clean_up_lst(t_list **lst);

// lst_hndl_type (handle token type)
t_type	handle_quotes(char *input, int *i);
t_type	handle_redir(char *input, int *i);
t_type	handle_env(char *input, int *i);
t_type	handle_words(char *input, int *i);
t_type	handle_pipe(int	*i);

// lst_clean (utils list clean up )
void	remove_type_rm(t_list **lst);
void	update_quotes(t_list **lst);
void	assign_word_type(t_list **lst);

// lst_word_typ
void	assign_file(t_list **node);
void	assign_cmd_and_args(t_list **cmd, t_list *node);
int		process_word(t_list **cmd, t_list **node);
// void	append_arg_to_cmd(t_list *cmd, t_list *arg);

// utl_ast (utils ast build)
// t_ast	*new_ast_node(t_list *lst);
// void	add_args_to_node(t_ast **ast, t_ast *arg);
// void	add_child_to_node(t_ast	**ast, t_ast *child, int side);
// void	free_ast(t_ast	*ast);

// utl_lst (utils list build)
t_list	*new_node(char *input, t_type type);
void	node_add_back(t_list **lst, t_list *new);
void	remove_node(t_list **lst, t_list **node);
void	add_arg(t_list *node, char *arg);
int		lstlen(t_list *lst);
void	free_lst(t_list **lst);
void	free_lst_redir(t_list *node);

// utl_pars (utils general)
int		is_redir(t_type	type);
int		is_operator(t_type type);

// prt_test (print tests)
void	prt_ast(t_list *lst);
// void	prt_lst(t_list *lst);
// void	rev_prt_lst(t_list *lst);

#endif