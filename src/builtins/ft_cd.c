/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:00:42 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/01 16:18:33 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **args, char ***envp)
{
	char	*oldpwd;
	char	*newpwd;
	char	*dir;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		ft_putstr_fd("cd: error retrieving current directory\n", 2);
	dir = get_dir(args, *envp);
	if (!dir)
		return ;
	if (chdir(dir) == -1)
	{
		perror("cd");
		free(oldpwd);
		return;
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		ft_putstr_fd("cd: error retrieving new directory\n", 2);
	if (oldpwd)
		mini_export(envp, ft_strjoin("OLDPWD=", oldpwd));
	if (newpwd)
		mini_export(envp, ft_strjoin("PWD=", newpwd));
	free(oldpwd);
	free(newpwd);
}

char	*get_dir(char **args, char **envp)
{
	char	*home;

	if (args[2])
		return (NULL); //error
	if (args[1])
		return (args[1]);
	home = ft_getenv(envp, "HOME");
	if (!home)
		ft_putstr_fd("cd: HOME not set\n", 2);
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
		if (!ft_strncmp(envp[i], name, len) &&  envp[i][len] == '=')
			return (envp[i] +  len + 1);
		i++;
	}
	return (NULL);
}
