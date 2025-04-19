/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:05:38 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/19 16:31:41 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// close the fd for the pipes after, function from PIPEX.
void	close_all(int n_cmd, int pipe_fd[])
{
	int	i;

	i = 0;
	while (i < (n_cmd - 1) * 2)
		close(pipe_fd[i++]);
	return ;
}

void close_wait(t_data *data, int n_cmd)
{
	int i;

	close_all(data);
	i = 0;
	while (i++ < n_cmd)
	{
		waitpid(-1, null, 0);
	}
	return ;
}
