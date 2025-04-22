/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:05:38 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/22 18:23:53 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	int i;

	close_all(ctx->n_cmd, ctx->pipe_fd);
	i = 0;
	while (i++ < ctx->n_cmd)
		waitpid(-1, NULL, 0);
}
