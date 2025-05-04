/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:47:37 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/01 16:23:34 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check when !cmd, and no content
void	ft_exit(t_list *cmd, t_data *data)
{
	long	exit_code;
	int		arg_count;
	char	*exit_arg;

	printf("exit\n");
	arg_count = count_args(cmd);
	exit_arg = cmd->content[1];
	exit_code = ft_atol(exit_arg);
	if (arg_count == 0)
		exit(g_exit_code);
	if (!ft_isdigit_str(exit_arg))
		file_exit_handler(data, "exit: ", exit_arg, ": numeric argument required", 2);
	if (arg_count > 1)
	{	
		error_handler("exit: too many arguments", 1);
		return ;
	}
	if (exit_code < 0 || exit_code > 255)
		exit_code %= 256;
	exit((int)exit_code);
	return ;
}
