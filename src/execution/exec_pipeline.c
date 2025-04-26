/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:10:49 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/23 11:44:05 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pipe_cmds(int n_cmd, int *pipe_fd)
{
	int	i;

	i = 0;
	while ((i < n_cmd - 1) && n_cmd > 1)
	{
		if (pipe(&pipe_fd[2 * i]) == -1)
		{
			perror("pipe error.\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void execmd(t_list *list, t_data *data)
{
	char *path;

	if (!list || !list->content || !list->content[0])
	{
		perror("cmd\n");
		exit(127);
	}
	path = pathfinder(list->content[0], data);
	if (!path)
	{
		free(path);
		perror("no path found.\n");
		exit(127);
	}
	if (execve(path, list->content, data->envp) == -1)
	{
		perror("execve\n");
		free(path);
		exit(1);
	}
	free(path);
	return ;
}

void child_process(t_exec_ctx *ctx)
{
	if (ctx->i != 0)
		dup2(ctx->pipe_fd[2 * (ctx->i - 1)], STDIN_FILENO);
	if (ctx->i != ctx->n_cmd - 1)
		dup2(ctx->pipe_fd[2 * ctx->i + 1], STDOUT_FILENO);
	close_all(ctx->n_cmd, ctx->pipe_fd);
	if (!ctx->node || ctx->node->type != CMD || !ctx->node->content)
		exit(EXIT_FAILURE);
	execmd(ctx->node, ctx->data);
}

int	exec_pipeline(t_list *start, t_data *data)
{
	int			pipe_fd[2 * MAX_PIPE];
	pid_t		pid;
	t_exec_ctx	ctx;

	init_exec_t(&ctx, pipe_fd, data, start);
	pipe_cmds(ctx.n_cmd, ctx.pipe_fd);
	while (ctx.i < ctx.n_cmd)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Error: fork.\n");
			return (EXIT_FAILURE);
		}
		if (pid == 0)
			child_process(&ctx);
		if (ctx.node)
			ctx.node = ctx.node->next;
		while (ctx.node && ctx.node->type != CMD)
			ctx.node = ctx.node->next;
		ctx.i++;
	}
	close_wait(&ctx);
	return (0);
}
