/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:07:20 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/10 13:09:47 by emurillo         ###   ########.fr       */
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
	dest[d++] = ' ';
	dest[d] = 0;
	return (dest);
}

char	*get_user(t_data *data)
{
	char	*name;

	name = replace_env(data, ft_strdup("$USER"));
	if (!name)
		return (NULL);
	if (!*name)
		return (ft_free(&name), ft_strdup("minishell"));
	return (name);
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
	if (dest[0] == 'c' && ft_isdigit(dest[1]) && dest[2] == 'r'
		&& ft_isdigit(dest[3]) && ft_strlen(dest) > 5
		&& ft_strlen(dest) < 9)
		return (dest);
	return (free(dest), ft_strdup("c4r2s42"));
}

// '/' root ; ~ instead of home/user ; rest is CWD -- LEAKS MALLOC CORRECTED
char	*get_cwd(t_data *data)
{
	int		home_len;
	char	*dest;
	char	*cwd;
	char	*home;
	char	*sufix;

	cwd = getcwd(NULL, 0);
	home = replace_env(data, ft_strdup("$HOME"));
	if (!home || !cwd)
		return (free(cwd), NULL);
	home_len = ft_strlen(home);
	sufix = ft_strdup(cwd + home_len);
	if(!sufix)
		return (free(home), free(cwd), NULL);
	if (!ft_strncmp(cwd, home, home_len))
	{
		if (!cwd[home_len])
			dest = ft_strdup("~");
		else
			dest = ft_strjoin_free_two("~", sufix);
	}
	else
		dest = ft_strdup(cwd);
	return (free(home), free(cwd), dest);
}
