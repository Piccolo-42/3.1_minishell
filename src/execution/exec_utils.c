/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 06:54:01 by emurillo          #+#    #+#             */
/*   Updated: 2025/05/07 12:01:21 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_cmds(int n_pipe, int *pipe_fd)
{
	int	i;

	i = 0;
	while (i < n_pipe)
	{
		if (pipe(&pipe_fd[2 * i]) == -1)
		{
			error_handler("pipe creation failed", 1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	execmd(t_list *list, t_data *data)
{
	char	*path;

	if (!*list->content[0])
		return (0);
	if (!list || !list->content || !list->content[0])
	{
		error_handler(" : command not found", 127);
		return (0);
	}
	path = pathfinder(list->content[0], data);
	if (!path)
	{
		file_error_handler(NULL, list->content[0], ": command not found", 127);
		return (0);
	}
	if (execve(path, list->content, data->envp) == -1)
	{
		file_error_handler(NULL, list->content[0], ": exec failed", 126);
		free(path);
		return (0);
	}
	free(path);
	return (1);
}

//error
int	child_process(t_exec_ctx *ctx)
{
	if (ctx->i != 0)
		dup2(ctx->pipe_fd[2 * (ctx->i - 1)], STDIN_FILENO);
	if (ctx->i != ctx->n_cmd - 1)//
		dup2(ctx->pipe_fd[2 * ctx->i + 1], STDOUT_FILENO);
	if (ctx->node && has_redirection(ctx->node))
	{	if (execute_redirections(ctx->node) == -1)
			return (0);
	}
	close_all(ctx->n_cmd, ctx->pipe_fd);
	if (!ctx->node || ctx->node->type != CMD || !ctx->node->content)
		return (file_error_handler(NULL, ctx->node->content[0], ": command not found", 127), 0);
	if (is_builtin(ctx->node->content[0]))
	{
		exec_builtin(ctx->node, ctx->data);
		return (1);
	}
	if (execmd(ctx->node, ctx->data))
		return (1);
	return (0);
}

int	count_pipe(t_list *start)
{
	int		n_pipe;
	t_list	*node;

	n_pipe = 0;
	node = start;
	while (node != NULL)
	{
		if (node->type == PIPE)
			n_pipe++;
		node = node->next;
	}
	return (n_pipe);
}

int	count_cmd(t_list *start)
{
	int		n_cmd;
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

void	init_exec_t(t_exec_ctx *ctx, int *pipe_fd, t_data *data, t_list *node)
{
	ctx->i = 0;
	ctx->n_cmd = count_cmd(node);
	ctx->n_pipe = count_pipe(node);
	if (ctx->n_pipe > 100)
		exit_handler(data, "too many pipes", 1);
	ctx->pipe_fd = pipe_fd;
	ctx->data = data;
	ctx->node = node;
}
