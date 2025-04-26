/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buit_ins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:07:30 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/24 15:14:04 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_buitin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strncmp(cmd, "cd", ft_strlen("cd"))
		|| !ft_strncmp(cmd, "echo", ft_strlen("echo"))
		|| !ft_strncmp(cmd, "env", ft_strlen("env"))
		|| !ft_strncmp(cmd, "pwd", ft_strlen("pwd"))
		|| !ft_strncmp(cmd, "export", ft_strlen("export"))
		|| !ft_strncmp(cmd, "unset", ft_strlen("unset"))
		|| !ft_strncmp(cmd, "exit", ft_strlen("exit")))
}

int	exec_buitin(t_list *node, t_data *data)
{
	char	*cmd;
	char	**args;
	char	***envp;

	if (!node || !node->content || !node->content[0])
		return (1);
	cmd = node->content[0];
	args = cmd_node->content;
	envp = &(*data)->envp;
	if (!ft_strncmp(cmd, "cd", 2))
		return (ft_cd(args, envp), 1);
	else if (!ft_strncmp(cmd, "echo", 4))
		return (ft_echo(args), 1);
	else if (!ft_strncmp(cmd, "env", 3))
		return (ft_env(*envp), 1);
	else if (!ft_strncmp(cmd, "export", 6))
		return (ft_export(envp, args), 1);
	else if (!ft_strncmp(cmd, "pwd", 3))
		return (ft_pwd(), 1);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (ft_unset(envp, args), 1);
	else if (!ft_strncmp(cmd, "exit", 4))
		return (ft_exit(node, &(*data)->error), 1);
	else
		return (0);
}
