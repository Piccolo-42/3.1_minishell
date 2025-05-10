/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:16:11 by emurillo          #+#    #+#             */
/*   Updated: 2025/05/10 11:00:27 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//error msg
int	execute_redir_in(t_list *cmd, t_data *data)
{
	t_list	*in;
	int		fd;

	in = cmd->read;
	if (in)
	{
		if (in->type == HEREDOC)
			fd = open(in->content[2], O_RDONLY);
		else if (in->type == REDIR_IN)
			fd = open(in->content[1], O_RDONLY);
		if (fd == -1 && in->type == HEREDOC)
			return (file_exit_handler(data, in->content[2],
					": No such file or directory", 2), -1);
		if (fd == -1 && in->type == REDIR_IN)
			return (file_exit_handler(data, in->content[1],
					": No such file or directory", 2), -1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (exit_handler(data, "dup2 in", 1), -1);
		close(fd);
	}
	return (1);
}

int	execute_redirections(t_list *cmd, t_data *data)
{
	t_list	*out;
	int		fd;

	execute_redir_in(cmd, data);
	out = cmd->write;
	if (out)
	{
		if (out->type == REDIR_OUT)
			fd = open(out->content[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (out->type == APPEND)
			fd = open(out->content[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			return (file_exit_handler(data, out->content[1],
					": No such file or directory", 2), -1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (exit_handler(data, "dup2 out", 1), -1);
		close(fd);
	}
	return (0);
}

int	has_redirection(t_list *cmd)
{
	if (!cmd || cmd->type != CMD)
		return (0);
	if (cmd->read || cmd->write)
		return (1);
	return (0);
}
