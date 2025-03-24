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


// parsing (main)
t_list	*parsing(char *input);
t_list	*token_lst(char *input);
void	clean_up_lst(t_list **lst);
t_list	*ast_build(t_list **lst);

// lst_hndl_type (handle token type)
t_type	get_type(char *input, int *i);
t_type	handle_quotes(char *input, int *i);
t_type	handle_redir(char *input, int *i);
t_type	handle_env(char *input, int *i);
t_type	handle_words(char *input, int *i);

// lst_clean (utils list clean up )
void	remove_type_rm(t_list **lst);
void	update_quotes(t_list **lst);
void	assign_word_type(t_list **lst);
void	assign_cmd_or_arg(t_list **cmd, t_list *node);
int		process_cmd_and_args(t_list **cmd, t_list **node);

// ast (Abstract Syntax Tree build)
t_list *process_redirs(t_list *cmd, t_list *redir);
t_list	*next_cmd(t_list **lst);
void	link_redirs_to_cmd(t_list **lst);
void	link_cmd_and_pipes(t_list **lst);

// ast_file_check
int		check_files(t_list *lst);
int		check_infile(t_list *node);
int		file_exists_and_is_readable(char *file);
int		check_outfile(t_list *node);
int		file_ok_or_create(char *file, t_type type);

// utl_lst_mk (utils list build)
int		create_token(char *input, t_list **lst);
t_list	*new_node(char *input, t_type type);
void	node_add_back(t_list **lst, t_list *new);
void	add_arg(t_list *node, char *arg);
int		lstlen(t_list *lst);

// utl_lst_rm (utils list remove/free)
void	remove_node(t_list **lst, t_list **node);
void	free_lst(t_list **lst);
void	free_lst_redir(t_list *node);

// utl_pars (utils general)
int		is_redir(t_type	type);
int		is_operator(t_type type);

// prt_test (print tests)
void	prt_ast(t_list *lst);
void	prt_lst(t_list *lst);
void	rev_prt_lst(t_list *lst);

#endif