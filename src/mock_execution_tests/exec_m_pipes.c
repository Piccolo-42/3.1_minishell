/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_m_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:49:27 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/10 15:30:52 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	ft_exec_pipeline(t_list *start, t_data *data)
{
	int		i;
	int		n_cmd;
	int		pipe_fd[2 * n_cmd];
	t_list	*node;
	pid_t	pid;

	n_cmd = 0;
	node = start;
	while (node)
	{
		if (node->type == CMD)
		n_cmd++;
		node = node->next;
	}
	i = 0;
	while (i < n_cmd)
	{
		pipe(&pipe_fd[2 * i]);
		i++;
	}

}


void	child(int i, int *fd, t_data *data, t_list *node)
{
	if (i == 0)
		ft_open(data->argv[1], data, 1); // if first cmd, read input from infile (or heredoc)
	else
		dup2(fd[(i - 1) * 2], STDIN_FILENO); // man dup2; else reads from previous pipe
	if (i == data->n_cmd - 1)
		ft_open(data->argv[data->argc - 1], data, 0); // if last, write output in outfile
	else
		dup2(fd[i * 2 + 1], STDOUT_FILENO); // else, write in previous pipe
	close_all(data); //close unused file descriptors and execute commands;
	exe(node->content, data);
}
