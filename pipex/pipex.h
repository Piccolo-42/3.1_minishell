/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:38:12 by sravizza          #+#    #+#             */
/*   Updated: 2025/01/20 15:23:48 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft_src/libft.h"
# include "libft/printf_src/ft_printf.h"
# include "libft/gnl_src/get_next_line.h"

typedef struct s_pipes
{
	int		argc;
	char	**argv;
	char	**envp;
	int		*fd;
	int		n_cmd;
	int		bonus;
}			t_pipe;

int		main(int argc, char **argv, char **envp);

//pipex.c
void	gnl_doc(char *limiter);
void	pipex(t_pipe *data);
void	child(int i, int *fd, t_pipe *data);
void	exe(char *argv, t_pipe *data);
char	*pathfinder(char *cmd, t_pipe *data);

//pipex_utils.c
void	error(char *str, t_pipe *data, int free_fd);
int		ft_open(char *file, t_pipe *data, int in);
void	free_all(char **str);
void	close_all(t_pipe *data);
void	close_and_wait_all(t_pipe *data);

#endif