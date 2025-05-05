/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:07:30 by emurillo          #+#    #+#             */
/*   Updated: 2025/05/05 17:42:42 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return ((!ft_strncmp(cmd, "cd", 2) && cmd[2] == '\0')
		|| (!ft_strncmp(cmd, "echo", 4) && cmd[4] == '\0')
		|| (!ft_strncmp(cmd, "env", 3) && cmd[3] == '\0')
		|| (!ft_strncmp(cmd, "pwd", 3) && cmd[3] == '\0')
		|| (!ft_strncmp(cmd, "export", 6) && cmd[6] == '\0')
		|| (!ft_strncmp(cmd, "unset", 5) && cmd[5] == '\0')
		|| (!ft_strncmp(cmd, "exit", 4) && cmd[4] == '\0')
	);
}

int	exec_builtin(t_list *node, t_data *data)
{
	char	*cmd;
	char	**args;
	char	***envp;

	if (!node || !node->content || !node->content[0])
		return (1);
	cmd = node->content[0];
	args = node->content;
	envp = &data->envp;
	if (!ft_strncmp(cmd, "cd", 2) && cmd[2] == '\0')
		return (ft_cd(args, envp, data), 1);
	else if (!ft_strncmp(cmd, "echo", 4) && cmd[4] == '\0')
		return (ft_echo(args), 1);
	else if (!ft_strncmp(cmd, "env", 3) && cmd[3] == '\0')
		return (ft_env(*envp), 1);
	else if (!ft_strncmp(cmd, "export", 6) && cmd[6] == '\0')
		return (ft_export(envp, args), 1);
	else if (!ft_strncmp(cmd, "pwd", 3) && cmd[3] == '\0')
		return (ft_pwd(data), 1);
	else if (!ft_strncmp(cmd, "unset", 5) && cmd[5] == '\0')
		return (ft_unset(envp, args), 1);
	else if (!ft_strncmp(cmd, "exit", 4) && cmd[4] == '\0')
		return (ft_exit(node, data), 1);
	else
		return (0);
}
