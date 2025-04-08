/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:46:20 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/08 21:17:26 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_create_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}


pid_t	exec_left(t_list *left, int fd[2])
{
	pid_t pid1;

	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execvp(left->content[0], left->content);
		perror("execvp left");
		exit(EXIT_FAILURE);
	}
	return (pid1);
}

pid_t	exec_right(t_list *right, int fd[2])
{
	pid_t pid2;

	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		execvp(right->content[0], right->content);
		perror("execvp left");
		exit(EXIT_FAILURE);
	}
	return (pid2);
}

void	ft_wait_pid(pid_t pid1, pid_t pid2)
{
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

/**
 * @brief Executes a pipe with two commands.
 *
 * This function manages the execution of two commands connected by a pipe. It
 * creates a pipe, forks processes for the left and right commands, and waits
 * for the processes to finish.
 *
 * @param left The left command node in the AST.
 * @param right The right command node in the AST.
 * @param envp The environment variables.
 */
void	ft_exec_pipe(t_list *left, t_list *right, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (ft_create_pipe(fd) == -1)
		return ;
	pid1 = exec_left(left, fd);
	pid2 = exec_right(right, fd);
	close(fd[0]);
	close(fd[1]);
	ft_wait_pid(pid1, pid2);
}
