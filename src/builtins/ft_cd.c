/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:00:42 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/07 16:25:10 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args, char ***envp, t_data *data)
{
	char	*oldpwd;
	char	*newpwd;
	char	*dir;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (exit_handler(data,
				"cd: error retrieving current directory\n", 1), 0);
	dir = get_dir(args, *envp);
	if (!dir)
		return (0);
	if (chdir(dir) == -1)
		return (ft_free(&oldpwd), file_error_handler("cd: ", dir,
				": no such file or directory", 1), 0);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (ft_free(&oldpwd),
			exit_handler(data, "cd: error retrieving new directory\n", 1), 0);
	mini_export(envp, ft_strjoin("OLDPWD=", oldpwd));
	mini_export(envp, ft_strjoin("PWD=", newpwd));
	ft_free(&oldpwd);
	ft_free(&newpwd);
	return (1);
}

char	*get_dir(char **args, char **envp)
{
	char	*home;
	int		n_arg;

	n_arg = 0;
	while (args[n_arg])
		n_arg++;
	if (n_arg > 2)
		return (error_handler("cd: too many arguments", 1), NULL);
	if (args[1] && ft_strncmp(args[1], "~", 1))
		return (args[1]);
	home = ft_getenv(envp, "HOME");
	if (!home)
		return (error_handler("cd: HOME not set", 1), NULL);
	return (home);
}

char	*ft_getenv(char **envp, char *name)
{
	int	i;
	int	len;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}
//file_error_handler(NULL, name, " not set", 1), 