/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:01:45 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/19 16:31:34 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define MAX_PIPE 100

# include "minishell.h"

//execution

void	ft_exec_ast(t_data *data);
void	ft_exec_pipe(t_list *left, t_list *right, char **envp);
void 	ft_exec_pipeline(t_list *start, t_data *data);


// for PATH search

char	*pathfinder(char *cmd, t_pipe *data);


// free **char anc waitpid

void free_all(char **str);
void close_wait(t_data *data, int n_cmd);
