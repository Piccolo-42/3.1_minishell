/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:47:37 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/28 15:57:23 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_list *cmd, int *exit_status)
{
	long	exit_code;
	int		arg_count;
	char	*exit_arg;

	printf("exit\n");
	arg_count = count_args(cmd);
	exit_arg = cmd->content[1];
	exit_code = ft_atol(exit_arg);
	if (arg_count == 0)
		exit(*exit_status);
	if (!ft_isdigit(exit_arg))
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", exit_arg);
		exit(2);
	}
	if (arg_count > 1)
	{	
		printf("minishell: exit: too many arguments");
		*exit_status = 1;
		return ;
	}
	if (exit_code < 0 || exit_code > 255)
		exit_code %= 256;
	exit((int)exit_code);
	return ;
}
