/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:16:33 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/25 17:00:12 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

// parsing (main)

t_list	*parsing(char *input);
t_list	*token_lst(char *input);


// get_type (handle token type)

t_type	get_type(char *input, int *i);
t_type	handle_quotes(char *input, int *i);
t_type	handle_redir(char *input, int *i);
t_type	handle_env(char *input, int *i);
t_type	handle_words(char *input, int *i);


// get_word_type

void	assign_word_type(t_list **lst);
void	assign_cmd_or_arg(t_list **cmd, t_list *node);
int		process_cmd_and_args(t_list **cmd, t_list **node);

//hndl_file_redir

void	assign_redir_and_file(t_list *node);
void	file_exists_and_is_readable(char *file);
void	file_ok_or_create(char *file, t_type type);
void	handle_here_doc(t_list *redir);
void	gnl_doc(char *limiter);


// link_read_write (redirs, pipes, cmd)

t_list *process_redirs(t_list *cmd, t_list *redir);
t_list	*next_cmd(t_list **lst);
void	link_redirs_to_cmd(t_list **lst);
void	link_cmd_and_pipes(t_list **lst);


// utl_clean (utils list clean up)

void	remove_type_rm(t_list **lst);
void	update_quotes(t_list **lst);
void	check_syntax(t_list **lst);


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
char	*ft_strjoin_free_one(char *str1, char *str2);


// X_prt_test (print tests)

void	prt_ast(t_list *lst);
void	prt_ast_read(t_list *lst, int i);
void	prt_ast_write(t_list *lst, int i, int lst_len);
void	prt_ast_content(t_list *lst, int i, int lst_len);

void	prt_lst(t_list *lst);
void	rev_prt_lst(t_list *lst);

void	prt_ast_colored(t_list *lst);
void	set_rest_red(t_list *lst);
void	set_rest_green(t_list *lst);
void	check_print(t_list *lst);

#endif