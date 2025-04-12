/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_m_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:49:27 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/12 16:54:28 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int		count_cmd(t_list *start, t_data *data);
static void		fork_and_dup(t_list *start, pid_t pid, int n_cmd, int pipe_fd[]);

void	ft_exec_pipeline(t_list *start, t_data *data)
{
	int		i;
	int		n_cmd;
	int		pipe_fd[2 * MAX_PIPE];
	pid_t	pid;

	i = 0;
	n_cmd = count_cmd(start, data);
	while ((i < n_cmd - 1) && n_cmd > 1)
	{
		if(pipe(&pipe_fd[2 * i]) == -1)
		{
			perror("pipe fail");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	fork_and_dup(start, pid, n_cmd, pipe_fd);
}


static void	fork_and_dup(t_list *start, pid_t pid, int n_cmd, int pipe_fd[])
{
	int	i;

	i = 0;
	while(i < n_cmd)
	{
		pid = fork();
		if (pid == -1)
			perror("fork() error.\n");
		if (pid == 0)
		{
			if (i == 0)
				dup2(pipe_fd[1], STDOUT_FILENO);
			else
				dup2(pipe_fd[i - 1 * 2], STDIN_FILENO);
			if (i == n_cmd - 1)
				dup2(pipe_fd[2 * (i - 1)], STDIN_FILENO);
			else
				dup2(pipe_fd[i * 2 + 1], STDOUT_FILENO);
		}
		close_all(n_cmd, pipe_fd);
	}
}

static int	count_cmd(t_list *start, t_data *data)
{
	int n_cmd;
	t_list	*node;

	n_cmd = 0;
	node = start;
	while (node != NULL)
	{
		if (node->type == CMD)
		n_cmd++;
		node = node->next;
	}
	return (n_cmd);
}

// close the fd for the pipes after, function from PIPEX.
void	close_all(int n_cmd, int pipe_fd[])
{
	int	i;

	i = 0;
	while (i < (n_cmd - 1) * 2)
		close(pipe_fd[i++]);
	return ;
}


/// pipex function to redirect the pipes input output.
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
