/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:27:00 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/02 11:41:07 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_handler(t_data *data, char *msg, int exit_code)
{
	data->exit_code = exit_code;
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
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

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->envp)
		ft_free_double(data->envp);
	if (data->input)
		ft_free(&(data->input));
	if (data->ast)
		free_lst(&(data->ast));
	// if (data->prompt)
	// 	free(data->prompt);
	ft_free_ptr((void **) &data);
}

