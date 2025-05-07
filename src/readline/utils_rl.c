/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:07:20 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/07 10:35:58 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	last_char(char *str)
{
	int		i;
	char	last;

	i = 0;
	last = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i]))
			last = str[i];
		i++;
	}
	return (last);
}

char	*fill_join(char *dest, char *name, char *session, char *cwd)
{
	int		i;
	int		d;

	d = 0;
	i = 0;
	while (name[i])
		dest[d++] = name[i++];
	dest[d++] = '@';
	i = 0;
	while (session[i])
		dest[d++] = session[i++];
	dest[d++] = ':';
	i = 0;
	while (cwd[i])
		dest[d++] = cwd[i++];
	dest[d++] = '$';
	dest[d++] = 'M';
	dest[d++] = 'S';
	dest[d++] = '$';
	dest[d] = 0;
	return (dest);
}

char	*custom_join(char *name, char *session, char *cwd)
{
	char	*dest;
	int		size;

	size = ft_strlen(name) + ft_strlen(session) + ft_strlen(cwd) + 4 + 3;
	if (size > 127)
		return (NULL);
	dest = malloc(sizeof(char) * size);
	if (!dest)
		return (NULL);
	dest = fill_join(dest, name, session, cwd);
	return (dest);
}

//if at 42, gets your computer location. else "c4r2s42"
char	*get_session(t_data *data)
{
	char	*dest;
	char	*env;
	int		i;

	env = replace_env(data, ft_strdup("$SESSION_MANAGER"));
	if (!env || !(*env))
		return (free(env), ft_strdup("c4r2s42"));
	i = 6;
	while (env[i] && env[i] != '.')
		i++;
	dest = ft_substr(env, 6, i - 6);
	free(env);
	if (!dest)
		return (NULL);
	return (dest);
}

// '/' root ; ~ instead of home/user ; rest is CWD
char	*get_cwd(t_data *data)
{
	int		home_len;
	char	*dest;
	char	*cwd;
	char	*home;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	home = replace_env(data, ft_strdup("$HOME"));
	if (!home)
		return (free(cwd), NULL);
	home_len = ft_strlen(home);
	if (!ft_strncmp(cwd, home, home_len))
	{
		if (!cwd[home_len])
			dest = ft_strdup("~");
		else
			dest = ft_strjoin_free_two("~", ft_strdup(cwd + home_len));
	}
	else
		dest = ft_strdup(cwd);
	return (free(home), free(cwd), dest);
}
