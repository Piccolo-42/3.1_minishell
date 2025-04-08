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
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define WHITE "\033[0m"
# define INT_MIN -2147483648
# define INT_MAX 2147483647

// readline

char	*read_input(void);
char	last_char(char *str);

//builtins

void	ft_cd(char **args, char ***envp);
char	*get_dir(char **args, char **envp);
char	*ft_getenv(char **envp, char *name);
void	ft_echo(char **args);
void	ft_env(char **envp);
int		ft_pwd(void);
void	ft_exit(t_list *cmd, int *exit_status);
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
char	**copy_envp(char **envp);
void	freef(char *format, ...);
void	ft_free(char *str);


#endif
