/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:27:00 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/10 11:10:01 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//errno : nbr
//perror : print error
//strerror : converts int to str strerror(errno)
//global g_exit_code

void	exit_handler(t_data *data, char *msg, int exit_code)
{
	error_handler(msg, exit_code);
	rl_clear_history();
	free_data(data);
	exit(exit_code);
}

void	file_exit_handler(t_data *data, char *str, char *file, int exit_code)
{
	g_exit_code = exit_code;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd("\n", 2);
	rl_clear_history();
	free_data(data);
	exit(exit_code);
}

void	silent_exit(t_data *data, int exit_code)
{
	g_exit_code = exit_code;
	rl_clear_history();
	free_data(data);
	exit(exit_code);
}

void	error_handler(char *msg, int exit_code)
{
	g_exit_code = exit_code;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	file_error_handler(char *first, char *file, char *second, int exit_code)
{
	g_exit_code = exit_code;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(first, 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(second, 2);
	ft_putstr_fd("\n", 2);
}
