/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hndl_file_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:07:04 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/02 15:04:10 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief after redir: WORD = FILE. checks/creates files
 */
void	assign_redir_and_file(t_list *redir, t_data *data)
{
	if (!redir->next )
	{
		error_handler(data, "syntax error near unexpected token 'newline'", 2);
		return ;
	}
	(redir->next)->type = FIL;
	add_arg(redir, (redir->next)->content[0]);
	remove_node(&redir, &redir->next);
	if (redir->type == REDIR_IN)
	 	file_exists_and_is_readable(redir->content[1]);
	if (redir->type == REDIR_OUT || redir->type == APPEND)
		file_ok_or_create(redir->content[1], redir->type);
	if (redir->type == HEREDOC)
		handle_here_doc(redir);
}

void	file_exists_and_is_readable(char *file,t_data *data)
{
	if (access(file, F_OK) != 0)
	{
		ft_putstr_fd(file, 2);
		error_handler(data, ":No such file or directory", 2);
		return;
	}
	if (access(file, R_OK) != 0)
	{
		// ft_putstr_fd("cannot open ", 2);
		// ft_putstr_fd(file, 2);
		perror("cannot open");
		strerror();
		ft_putstr_fd("permission denied ", 2);
		error_handler(data, "", 126);
		return;
	}
	// printf("%s OK\n", file);
	return ;
}

void	file_ok_or_create(char *file, t_type type)
{
	int	fd;

	if (type == REDIR_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		//error code
		printf("problem opening %s\n", file);
		return ;
	}
	printf("%s OK\n", file);
	close(fd);
	return ;
}

void	handle_here_doc(t_list *redir)
{
	char *line;
	char *total;
	char *limiter;

	limiter = redir->content[1];
	// printf("here_doc, limiter: %s\n", limiter);
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
	add_arg(redir, total);
	free(total);
	printf("here_doc, doc:\n%s", redir->content[2]);
}

