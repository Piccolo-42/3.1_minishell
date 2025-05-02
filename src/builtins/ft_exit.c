/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:47:37 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/02 16:59:21 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check when !cmd, and no content
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
	if (!ft_isdigit_str(exit_arg))
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
	exit((int)exit_code % 256);
	return ;
}
