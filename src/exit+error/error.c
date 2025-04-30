/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:27:00 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/30 14:23:46 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	exit_freef(t_data *data, int exit_code, char *format, ...)
// {
// 	int		i;
// 	va_list	args;

// 	if (!format)
// 		return ;
// 	va_start(args, format);
// 	i = 0;
// 	while(format[i])
// 	{
// 		if (format[i] == 's')
// 			ft_free(va_arg(args, char *));
// 		if (format[i] == 'd')
// 			free_double(va_arg(args, char **));
// 		if (format[i] == 'l')
// 			free_lst(va_arg(args, t_list **));
// 		i++;
// 	}
// 	va_end(args);
// 	exit(exit_code);
// 	return ;
// }

void	ft_free(void **ptr)
{
	if (!(*ptr))
	{
		(*ptr) = NULL;
		return;
	}
	free((*ptr));
	return ;
}
