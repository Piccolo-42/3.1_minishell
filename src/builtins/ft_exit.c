/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:47:37 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/05 17:37:25 by emurillo         ###   ########.fr       */
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
	{
		file_error_handler("exit: ",
			exit_arg, ": numeric argument required", 2);
		exit_handler(data, NULL, 2);
	}
	if (arg_count > 1)
	{
		error_handler("exit: too many arguments", 1);
		return ;
	}
	if (exit_code < 0 || exit_code > 255)
		exit_code %= 256;
	silent_exit(data, (int)exit_code);
	return ;
}
