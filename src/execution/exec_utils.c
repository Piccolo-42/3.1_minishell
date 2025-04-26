/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 06:54:01 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/26 18:19:38 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	execmd(t_list *list, t_data *data)
{
	char	*path;

	if (!list || !list->content || !list->content[0])
	{
		ft_putstr_fd("Error: empty command\n", 2);
		exit(127);
	}
	path = pathfinder(list->content[0], data);
	if (!path)
	{
		ft_putstr_fd(list->content[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (execve(path, list->content, data->envp) == -1)
	{
		perror("execve");
		free(path);
		exit(1);
	}
	free(path);
	return ;
}

void	child_process(t_exec_ctx *ctx)
{
	if (ctx->i != 0)
		dup2(ctx->pipe_fd[2 * (ctx->i - 1)], STDIN_FILENO);
	if (ctx->i != ctx->n_cmd - 1)
		dup2(ctx->pipe_fd[2 * ctx->i + 1], STDOUT_FILENO);
	close_all(ctx->n_cmd, ctx->pipe_fd);
	if (!ctx->node || ctx->node->type != CMD || !ctx->node->content)
		exit(EXIT_FAILURE);
	if (is_builtin(ctx->node->content[0]))
	{
		exec_builtin(ctx->node, ctx->data);
		exit(EXIT_SUCCESS);
	}
	else
		execmd(ctx->node, ctx->data);
	exit(EXIT_FAILURE);
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
	ctx->pipe_fd = pipe_fd;
	ctx->data = data;
	ctx->node = node;
}
