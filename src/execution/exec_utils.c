/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 06:54:01 by emurillo          #+#    #+#             */
/*   Updated: 2025/05/08 10:38:00 by emurillo         ###   ########.fr       */
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
		file_exit_handler(NULL, list->content[0], ": command not found", 127);
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

int	init_exec_t(t_exec_ctx *ctx, int *pipe_fd, t_data *data, t_list *node)
{
	ctx->i = 0;
	ctx->n_cmd = count_cmd(node);
	ctx->n_pipe = count_pipe(node);
	if (ctx->n_pipe > 100)
		return (error_handler("too many pipes", 1), 0);
	ctx->pipe_fd = pipe_fd;
	ctx->data = data;
	ctx->node = node;
	return (1);
}
