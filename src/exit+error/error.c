/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:27:00 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/02 15:27:26 by sravizza         ###   ########.fr       */
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

void	file_exit_handler(t_data *data, char *first, char *file, char *second, int exit_code)
{
	file_error_handler(first, file, second, exit_code);
	rl_clear_history();
	free_data(data);
	exit(exit_code);
}

void	error_handler(char *msg, int exit_code)
{
	g_exit_code = exit_code;
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	file_error_handler(char *first, char *file, char *second, int exit_code)
{
	g_exit_code = exit_code;
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(first, 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(second, 2);
	ft_putstr_fd("\n", 2);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	ft_free_double(data->envp);
	ft_free(&(data->input));
	if (data->ast)
		free_lst(&(data->ast));
	if (data->prompt)
		ft_free(&(data->prompt));
	free(data);
}

void	exit_freef(t_data *data, int exit_code, char *format, ...)
{
	int		i;
	va_list	args;

	if (format)
	{	
		va_start(args, format);
		i = 0;
		while(format[i])
		{
			if (format[i] == 's')
				free(va_arg(args, char *));
			if (format[i] == 'd')
				ft_free_double(va_arg(args, char **));
			if (format[i] == 'l')
				free_lst(va_arg(args, t_list **));
			i++;
		}
		va_end(args);
	}
	rl_clear_history();
	free_data(data);
	exit(exit_code);
	return ;
}

