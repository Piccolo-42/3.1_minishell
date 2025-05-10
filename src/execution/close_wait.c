/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:05:38 by emurillo          #+#    #+#             */
/*   Updated: 2025/05/10 11:59:13 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// close the fd for the pipes after, function from PIPEX.
void	close_all(int n_cmd, int pipe_fd[])
{
	int	i;

	i = 0;
	while (i < (n_cmd - 1) * 2)
		close(pipe_fd[i++]);
	return ;
}

void	close_wait(t_exec_ctx *ctx)
{
	int	i;
	int	status;

	close_all(ctx->n_cmd, ctx->pipe_fd);
	i = 0;
	while (i++ < ctx->n_cmd)
	{
		if (waitpid(-1, &status, 0) != -1)
		{
			if (WIFEXITED(status))
				g_exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					ft_putendl_fd("Quit (core dumped)", 2);
				g_exit_code = 128 + WTERMSIG(status);
			}
		}
	}
}

// void	close_wait(t_exec_ctx *ctx)
// {
// 	int	i;
// 	int	status;

// 	close_all(ctx->n_cmd, ctx->pipe_fd);
// 	i = 0;
// 	while (i++ < ctx->n_cmd)
// 	{
// 		if (waitpid(-1, &status, 0) != -1)
// 		{
// 			if (WIFSIGNALED(status) && WIFSIGNALED(status) != 0)
// 			{
// 				if (WTERMSIG(status) == SIGQUIT)
// 					ft_putendl_fd("Quit (core dumped)", 2);
// 			}
// 			if ((status) == 0)
// 				g_exit_code = (status >> 8) & 0xFF;
// 			else
// 				g_exit_code = 128 + (status & 0x7F);
// 		}
// 	}
// }
