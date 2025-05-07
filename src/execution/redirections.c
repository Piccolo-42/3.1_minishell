/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:16:11 by emurillo          #+#    #+#             */
/*   Updated: 2025/05/06 17:17:21 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_redirections(t_list *cmd)
{
	t_list	*in;
	t_list	*out;
	int		fd;

	in = cmd->read;
	// printf("in 0: %s\n", in->content[0]);
	// printf("in 1: %s\n", in->content[1]);

	if (in)
	{
		if (in->type == HEREDOC)
			fd = open(in->content[2], O_RDONLY);
		else if (in->type == REDIR_IN)
			fd = open(in->content[1], O_RDONLY);
		if (fd == -1)
			return (perror("infile"), -1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return(perror("dup2 in"), -1);
		close(fd);
	}
	out = cmd->write;
	if (out)
	{
		if (out->type == REDIR_OUT)
			fd = open(out->content[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (out->type == APPEND)
			fd = open(out->content[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			return (perror("outfile"), -1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return(perror("dup2 out"), -1);
		close(fd);
	}
	// printf("out 0: %s\n", out->content[0]);
	// printf("out 1: %s\n", out->content[1]);
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
