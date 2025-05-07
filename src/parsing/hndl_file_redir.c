/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hndl_file_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:07:04 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/07 12:23:27 by sravizza         ###   ########.fr       */
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
	if (redir->type == HEREDOC && !handle_here_doc(redir, data))
	{
		data->prt = 0;
		return (0);
	}
	return (1);
}

//check error n2
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
		return (0);
	}
	return (1);
}

//check err2
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
		return (0);
	}
	close(fd);
	return (1);
}

int	here_doc_readline(char *limiter, int doc_fd, t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if ((!line) || (line && !ft_strncmp(line, limiter, ft_strlen(limiter))
				&& ft_strlen(line) == ft_strlen(limiter)))
		{
			ft_free(&line);
			break ;
		}
		line = dblq_replace_env(data, line);
		if (!line)
			return (0);
		write(doc_fd, line, ft_strlen(line));
		write(doc_fd, "\n", 1);
		free(line);
	}
	return (1);
}

int	handle_here_doc(t_list *redir, t_data *data)
{
	char	*limiter;
	int		doc_fd;
	char	*doc_name;

	doc_name = ft_strjoin_free_two(".heredoc_", ft_itoa(data->here_doc));
	if (!doc_name)
		return (0);
	limiter = redir->content[1];
	doc_fd = open(doc_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (doc_fd == -1)
	{
		error_handler("heredoc: failed to create temporary file", 1);
		free(doc_name);
		return (0);
	}
	if (!here_doc_readline(limiter, doc_fd, data))
		return (0);
	close(doc_fd);
	if (!add_arg(redir, doc_name))
		return (free(doc_name), 0);
	return (free(doc_name), 1);
}

// int	handle_here_doc(t_list *redir, t_data *data)
// {
// 	char	*line;
// 	char	*total;
// 	char	*limiter;

// 	limiter = redir->content[1];
// 	total = ft_calloc(1, 1);
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if ((!line) || (line && !ft_strncmp(line, limiter, ft_strlen(limiter))
// 			&& ft_strlen(line) == ft_strlen(limiter)))
// 		{
// 			ft_free(&line);
// 			break ;
// 		}
// 		total = ft_strjoin_free_one(total, line);
// 		total = ft_strjoin_free_one(total, "\n");
// 		free(line);
// 	}
// 	if (!add_arg(redir, total))
// 		return (free(total), 0);
// 	free(total);
// 	return (1);
// }
