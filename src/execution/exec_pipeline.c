/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:10:49 by emurillo          #+#    #+#             */
/*   Updated: 2025/05/02 18:35:28 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_redirections(t_list *cmd)
{
	t_list	*in;
	t_list	*out;
	int		fd;

	in = cmd->read;
	while (in)
	{
		fd = open(in->content[0], O_RDONLY);
		if (fd == -1)
			return (perror("infile"), -1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return(perror("dup2 in"), -1);
		close(fd);
		in = in->next;
	}
	out = cmd->write;
	printf("Redirecting stdout to: %s\n", out->content[0]);
	while (out)
	{
		fd = open(out->content[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			return (perror("outfile"), -1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return(perror("dup2 out"), -1);
		close(fd);
		out = out->next;
	}
	return (0);
}

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
	int			save_in;
	int			save_out;

	init_exec_t(&ctx, pipe_fd, data, start);
	if (ctx.n_cmd == 1 && is_builtin(ctx.node->content[0]))
	{
		save_in = dup(STDIN_FILENO);
		save_out = dup(STDOUT_FILENO);
		if (execute_redirections(ctx.node) == -1)
			return (1);
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
