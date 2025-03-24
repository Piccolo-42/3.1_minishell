/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_file_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:00:30 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/24 16:51:03 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * @return 1 if files are ok, 0 if any problem
 */
int	check_files(t_list *lst)
{
	while (lst)
	{
		if (lst->type == CMD && lst->read && !check_infile(lst))
			return (0);
		if (lst->type == CMD && lst->write && !check_outfile(lst))
			return (0);
		lst = lst->next;
	} 
	return (1);
}

int	check_infile(t_list *node)
{
	t_list	*redir;

	redir = node->read;
	while (redir)
	{
		if (!redir->content[1])
			return (0);
		if (redir->type == REDIR_IN
				&& !file_exists_and_is_readable(redir->content[1]))
			return (0);
		redir = redir->next;
	}
	return (1);
}

int	file_exists_and_is_readable(char *file)
{
	if (access(file, F_OK) == 0 && access(file, R_OK) == 0)
		return (1);
	return (0);
}

int	check_outfile(t_list *node)
{
	t_list	*redir;

	redir = node->write;
	while (redir)
	{
		if (!redir->content[1])
			return (0);
		if (!file_ok_or_create(redir->content[1], redir->type))
			return (0);
		redir = redir->next;
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
		return (0);
	close(fd);
	return (1);
}
