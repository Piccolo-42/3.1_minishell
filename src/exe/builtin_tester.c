/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_tester.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:22:21 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/30 17:05:37 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pick_builtin(t_list *cmd_node, t_data **data)
{
	char	*cmd;
	char	**args; 
	char	***envp;

	cmd = cmd_node->content[0];
	args = cmd_node->content;
	envp = &(*data)->envp;
	if (!ft_strncmp(cmd, "cd", 2))
		return (ft_cd(args, envp), 1);
	else if (!ft_strncmp(cmd, "echo", 4))
		return (ft_echo(args), 1);
	else if (!ft_strncmp(cmd, "env", 3))
		return (ft_env(*envp), 1);
	else if (!ft_strncmp(cmd, "exit", 4))
		return (ft_exit(cmd_node, &(*data)->error), 1);
	else if (!ft_strncmp(cmd, "export", 6))
		return (ft_export(envp, args), 1);
	else if (!ft_strncmp(cmd, "pwd", 3))
		return (ft_pwd(), 1);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (ft_unset(envp, args), 1);
	else
		return (0);
}

void	builtin_tester(t_data **data)
{
	t_list *lst;

	lst = (*data)->ast;
	if (!lst)
		return;
	while (lst)
	{
		if (lst->type == CMD)
		{
			if (!pick_builtin(lst, data))
				printf("%s: is not a builtin\n", lst->content[0]);
		}
		lst = lst->next;
	}
	return ;
}
