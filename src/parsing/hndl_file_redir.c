/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hndl_file_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:07:04 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/05 17:20:10 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief after redir: WORD = FILE. checks/creates files
 */
int	assign_redir_and_file(t_list *redir, t_data *data)
{
	if (!redir->next)
		return (error_handler(
				"syntax error near unexpected token 'newline'", 2), 0);
	(redir->next)->type = FIL;
	if (!add_arg(redir, (redir->next)->content[0]))
		return (0);
	remove_node(&redir, &redir->next);
	if (redir->type == REDIR_IN
		&& !file_exists_and_is_readable(redir->content[1]))
	{
		data->prt = 0;
		return (0);
	}
	if ((redir->type == REDIR_OUT || redir->type == APPEND)
		&& !file_ok_or_create(redir->content[1], redir->type))
	{
		data->prt = 0;
		return (0);
	}
	if (redir->type == HEREDOC && !handle_here_doc(redir))
	{
		data->prt = 0;
		return (0);
	}
	return (1);
}

int	file_exists_and_is_readable(char *file)
{
	if (access(file, F_OK) != 0)
	{
		file_error_handler(NULL, file, ": No such file or directory", 2);
		return (0);
	}
	if (access(file, R_OK) != 0)
	{
		file_error_handler("cannot open ", file, " permission denied", 126);
		return (0); //check
	}
	return (1);
}

int	file_ok_or_create(char *file, t_type type)
{
	int	fd;

	if (type == REDIR_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		file_error_handler("cannot open ", file, " permission denied", 126);
		return (0); //check
	}
	close(fd);
	return (1);
}

int	handle_here_doc(t_list *redir)
{
	char	*line;
	char	*total;
	char	*limiter;

	limiter = redir->content[1];
	total = ft_calloc(1, 1);
	total = NULL;
	while (1)
	{
		line = readline(">: ");
		if (line && !ft_strncmp(line, limiter, ft_strlen(limiter))
			&& ft_strlen(line) == ft_strlen(limiter))
		{
			free(line);
			break ;
		}
		total = ft_strjoin_free_one(total, line);
		total = ft_strjoin_free_one(total, "\n");
		free(line);
	}
	if (!add_arg(redir, total))
		return (0);
	free(total);
	return (1);
}
