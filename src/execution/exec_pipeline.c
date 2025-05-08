/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:10:49 by emurillo          #+#    #+#             */
/*   Updated: 2025/05/08 14:38:15 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_multiple_args(t_exec_ctx *ctx)
{
	pid_t	pid;

	if (!pipe_cmds(ctx->n_cmd, ctx->pipe_fd))
		return (0);
	while (ctx->node && ctx->i < ctx->n_cmd)
	{
		if (ctx->node->type == CMD)
		{
			pid = fork();
			if (pid == -1)
				error_handler("fork failed", 1);
			if (pid == 0)
			{
				child_signal(ctx->data);
				signal(SIGINT, SIG_DFL);
				// signal(SIGQUIT, SIG_DFL);
				child_process(ctx);
			}
			signal_init(ctx->data);
			ctx->i++;
		}
		ctx->node = ctx->node->next;
	}
	close_wait(ctx);
	return (0);
}
// if (ctx->node)
// 	ctx->node = ctx->node->next;
// while (ctx->node && ctx->node->type != CMD)
// 	ctx->node = ctx->node->next;

int	exec_pipeline(t_list *start, t_data *data)
{
	int			pipe_fd[2 * MAX_PIPE];
	t_exec_ctx	ctx;
	int			save_in;
	int			save_out;

	if (!init_exec_t(&ctx, pipe_fd, data, start))
		return (0);
	if (ctx.node && ctx.n_cmd == 1 && is_builtin(ctx.node->content[0]))
	{
		save_in = dup(STDIN_FILENO);
		save_out = dup(STDOUT_FILENO);
		if (has_redirection(ctx.node) && execute_redirections(ctx.node) == -1)
			return (0);
		g_exit_code = exec_builtin(ctx.node, ctx.data);
		dup2(save_in, STDIN_FILENO);
		dup2(save_out, STDOUT_FILENO);
		close(save_in);
		close(save_out);
		return (0);
	}
	if (!exec_multiple_args(&ctx))
		return (0);
	g_exit_code = 0;;
	return (1);
}

//error
int	child_process(t_exec_ctx *ctx)
{
	if (ctx->i != 0)
		dup2(ctx->pipe_fd[2 * (ctx->i - 1)], STDIN_FILENO);
	if (ctx->i != ctx->n_cmd - 1)
		dup2(ctx->pipe_fd[2 * ctx->i + 1], STDOUT_FILENO);
	if (ctx->node && has_redirection(ctx->node))
	{
		if (execute_redirections(ctx->node) == -1)
			return (0);
	}
	close_all(ctx->n_cmd, ctx->pipe_fd);
	if (!ctx->node || ctx->node->type != CMD || !ctx->node->content)
		return (ft_putendl_fd("here error.", 2)/* file_exit_handler(ctx->data,
				ctx->node->content[0], ": command not found", NULL, 127),*/, 0);
	if (is_builtin(ctx->node->content[0]))
	{
		exec_builtin(ctx->node, ctx->data);
		return (1);
	}
	if (!execmd(ctx->node, ctx->data))
		return (0);
	return (1);
}
