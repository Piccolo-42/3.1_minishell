/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:01:45 by emurillo          #+#    #+#             */
/*   Updated: 2025/05/08 17:42:39 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define MAX_PIPE 100

# include "minishell.h"

//execution

int		exec_pipeline(t_list *start, t_data *data);
int		count_cmd(t_list *start);
int		init_exec_t(t_exec_ctx *ctx, int *pipe_fd, t_data *data, t_list *node);
int		child_process(t_exec_ctx *ctx);
int		pipe_cmds(int n_cmd, int *pipe_fd);
int		exec_builtin(t_list *node, t_data *data);
int		is_builtin(char *cmd);
int		execute_redirections(t_list *cmd, t_data *data);
int		has_redirection(t_list *cmd);
int		execmd(t_list *list, t_data *data);


// for PATH search

char	*pathfinder(char *cmd, t_data *data);


// free **char anc waitpid

void	free_all(char **str);
void	close_all(int n_cmd, int pipe_fd[]);
void	close_wait(t_exec_ctx *ctx);

#endif
