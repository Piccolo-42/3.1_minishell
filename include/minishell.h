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
# include "typedef.h"
# include "parsing.h"
# include "execution.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define WHITE "\033[0m"
# define INT_MIN -2147483648
# define INT_MAX 2147483647

extern int g_exit_code;

// readline
char	*read_input(t_data *data);
char	*prompt(t_data *data);
char	*custom_join(char *name, char *session, char *cwd);
char	*get_session(t_data *data);
char	*get_cwd(t_data *data);
char	last_char(char *str);

//builtins

int		ft_cd(char **args, char ***envp, t_data *data);
char	*get_dir(char **args, char **envp);
char	*ft_getenv(char **envp, char *name);
void	ft_echo(char **args);
void	ft_env(char **envp);
int		ft_pwd(t_data *data);
void	ft_exit(t_list *cmd, t_data *data);
int		count_args(t_list *node);
void	ft_export(char ***envp, char **args);
int		ft_varlen(char *name);
void	ft_unset(char ***evnp, char **args);
void	print_export(char **envp);
void	mini_export(char ***envp, char *var);
void	mini_unset(char ***envp, char *name);
char	**sort_export(char **envp);

//execs

void	ft_exec_ast(t_data *data);
void	ft_exec_pipe(t_list *left, t_list *right, char **envp);

//main

void	builtin_tester(t_data **data);
t_data	*init_data(char **envp);
char	**copy_envp(char **envp);
char	**empty_envp(void);

//error
void	exit_freef(t_data *data, int exit_code, char *format, ...);
void	exit_handler(t_data *data, char *msg, int exit_code);
void	silent_exit(t_data *data, int exit_code);
void	file_error_handler(char *first, char *file, char *second, int exit_code);
void	file_exit_handler(t_data *data, char *str, char *file, int exit_code);
void	error_handler(char *msg, int exit_code);
void	free_data(t_data *data);

//signals
void	signal_init(t_data *data);
void	handle_signint(int signum);
void	child_signal(t_data *data);

// void	freef(char *format, ...);


#endif
