/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:39:03 by sravizza          #+#    #+#             */
/*   Updated: 2025/01/20 15:32:32 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *str, t_pipe *data, int free_fd)
{
	if (free_fd)
		free(data->fd);
	ft_putstr_fd(str, 2); //writes str (error message) on the terminal (stdout)
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

int	ft_open(char *file, t_pipe *data, int in)
{
	int	fd;

	// Open file for reading (input redirection)
	if (in)
	{
		if (data->bonus)
			fd = open(".tmp_doc", O_RDONLY); //here_doc
		else
			fd = open(file, O_RDONLY);
		if (fd == -1)
			error("open file fail", data, 1);
		dup2(fd, STDIN_FILENO);
	}
	// Open file for writing (output redirection)
	else
	{
		if (data->bonus)
			fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			error("open file fail", data, 1);
		dup2(fd, STDOUT_FILENO);
	}
	close(fd);
	return (fd);
}

void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return ;
}

void	close_and_wait_all(t_pipe *data)
{
	int	i;

	// Close all open file descriptors
	close_all(data);
	i = 0;
	// Wait for all child processes to finish
	while (i++ < data->n_cmd)
		waitpid(-1, NULL, 0); //man waitpid
	if (data->bonus)
		unlink(".tmp_doc"); //rm temp here_doc file
	free(data->fd);
	return ;
}

void	close_all(t_pipe *data)
{
	int	i;

	i = 0;
	while (i < (data->n_cmd - 1) * 2)
		close(data->fd[i++]);
	return ;
}
