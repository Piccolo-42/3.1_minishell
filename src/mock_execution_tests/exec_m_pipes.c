/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_m_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:49:27 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/19 16:40:57 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_cmd(t_list *start, t_data *data);
static void	fork_and_dup(t_list *start, pid_t pid, t_data *data, int pipe_fd[]);

void free_all(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i++]);
	}
	free(str);
}


void execmd(char *argv, t_data *data)
{
	char **cmd;
	char *path;

	cmd = ft_split(argv, ' ');
	if (!cmd || !cmd[0])
	{
		free_all(cmd);
		perror('Error: cmd');
	}
	path = pathfinder(cmd[0], data);
	if (!path)
	{
		ft_putstr_fd(cmd[0], 2);
		free_all(cmd);
		free(path);
		ft_putstr_fd(":command not found", 2);
		exit(127);
	}
	if (execve(path, cmd, data->envp) == -1)
	{
		free(cmd);
		free(path);
		error("exe error");
	}
	free(path);
	return ;
}

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
	close
}

static void	fork_and_dup(t_list *start, pid_t pid, t_data *data, int pipe_fd[])
{
	int	i;
	int	n_cmd;

	i = 0;
	n_cmd = count_cmd(start, data);
	while(i < n_cmd)
	{
		pid = fork();
		if (pid == -1)
			perror("fork() error.\n");
		if (pid == 0)
		{
			if (i != 0)
				dup2(pipe_fd[2 * (i - 1)], STDIN_FILENO);
			if (i != n_cmd -1)
				dup2(pipe_fd[(i * 2) + 1], STDOUT_FILENO);
		}
		close_all(n_cmd, pipe_fd);
		execmd(start->content, data);
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

