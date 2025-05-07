/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:10:49 by emurillo          #+#    #+#             */
/*   Updated: 2025/05/07 15:05:19 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_multiple_args(t_exec_ctx *ctx)
{
	pid_t	pid;

	pipe_cmds(ctx->n_cmd, ctx->pipe_fd);
	while (ctx->node && ctx->i < ctx->n_cmd)
	{
		if (ctx->node->type == CMD)
		{
			pid = fork();
			if (pid == -1)
			{
				exit_handler(ctx->data, "fork failed", 1);
			}
			if (pid == 0)
				child_process(ctx);
			if (ctx->node)
			 	ctx->node = ctx->node->next;
			while (ctx->node && ctx->node->type != CMD)
			 	ctx->node = ctx->node->next;
			ctx->i++;
		}
		ctx->node = ctx->node->next;
	}
	close_wait(ctx);
	return (0);
}

int checker_built_redir(t_exec_ctx ctx)
{
	int	save_in
	int	save_out;

	if (ctx.node && ctx.n_cmd == 1
		&& is_builtin(ctx.node->content[0])
		&& lstlen(data->ast) == 1)
	{
		save_in = dup(STDIN_FILENO);
		save_out = dup(STDOUT_FILENO);
		if (has_redirection(ctx.node))
		{
			if (execute_redirections(ctx.node) == -1)
				return (1);
		}
		exec_builtin(ctx.node, ctx.data);
		dup2(save_in, STDIN_FILENO);
		dup2(save_out, STDOUT_FILENO);
		close(save_in);
		close(save_out);
		return (0);
	}
}

int	exec_pipeline(t_list *start, t_data *data)
{
	int			pipe_fd[2 * MAX_PIPE];
	t_exec_ctx	ctx;
	int			save_in;
	int			save_out;

	init_exec_t(&ctx, pipe_fd, data, start);
	if (ctx.node && ctx.n_cmd == 1 && is_builtin(ctx.node->content[0]) && lstlen(data->ast) == 1)
	{
		save_in = dup(STDIN_FILENO);
		save_out = dup(STDOUT_FILENO);
		if (has_redirection(ctx.node))
		{
			if (execute_redirections(ctx.node) == -1)
				return (1);
		}
		exec_builtin(ctx.node, ctx.data);
		dup2(save_in, STDIN_FILENO);
		dup2(save_out, STDOUT_FILENO);
		close(save_in);
		close(save_out);
		return (0);
	}
	exec_multiple_args(&ctx);
	return (0);
}
