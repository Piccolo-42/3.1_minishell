/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:10:49 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/26 18:32:40 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_multiple_args(t_exec_ctx *ctx)
{
	pid_t	pid;

	pipe_cmds(ctx->n_cmd, ctx->pipe_fd);
	while (ctx->i < ctx->n_cmd)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Error: fork.\n");
			return (EXIT_FAILURE);
		}
		if (pid == 0)
			child_process(ctx);
		if (ctx->node)
			ctx->node = ctx->node->next;
		while (ctx->node && ctx->node->type != CMD)
			ctx->node = ctx->node->next;
		ctx->i++;
	}
	close_wait(ctx);
	return (0);
}

int	exec_pipeline(t_list *start, t_data *data)
{
	int			pipe_fd[2 * MAX_PIPE];
	t_exec_ctx	ctx;

	init_exec_t(&ctx, pipe_fd, data, start);
	if (ctx.n_cmd == 1 && is_builtin(ctx.node->content[0]))
	{
		exec_builtin(ctx.node, ctx.data);
		return (0);
	}
	exec_multiple_args(&ctx);
	return (0);
}
