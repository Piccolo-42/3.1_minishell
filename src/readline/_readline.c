/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _readline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:59:49 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/01 22:16:54 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*read_input(void)
// {
// 	char	*input;
// 	char	*line;

// 	input = NULL;
// 	while (1)
// 	{
// 		line = readline(">: ");
// 		if (!line || !ft_strncmp(line, "exit", 4))
// 			return (NULL);
// 		input = ft_strjoin(input, line);
// 		if (!input)
// 			return (free(line), NULL);
// 		else if (last_char(line) != '|')
// 		{
// 			free(line);
// 			break ;
// 		}
// 		free(line);
// 	}
// 	return (input);
// }

//simple version, no "keep reading" after an open pipe (see above)
char	*read_input(t_data *data)
{
	char	*line;

	prt_prompt(data);
	// if (data)
	ft_printf(">:");
	line = readline("");
	if (!line)
		return (NULL);
	if (!ft_strncmp(line, "exit", 4))
		return (free(line), NULL);

	return (line);
}

//prints USER@c4r2s42:CWD$
void	prt_prompt(t_data *data)
{
	char	*name;
	char	*session;
	char	*cwd;

	name = replace_env(data, ft_strdup("$USER"));
	if (!name)
		return ;
	session = get_session(data);
	if (!session)
		return ;
	cwd = get_cwd(data);
	if (!cwd)
		return ;
	ft_printf("%s@%s:%s$", name, session, cwd);
	free(name);
	free(session);
	free(cwd);
}

//if at 42, gets your computer location. else "c4r2s42"
char	*get_session(t_data *data)
{
	char	*dest;
	char	*env;
	int		i;

	env = replace_env(data, ft_strdup("$SESSION_MANAGER"));
	if (!env || !(*env))
		return(ft_strdup("c4r2s42"));
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

	cwd = replace_env(data, ft_strdup("$PWD"));
	if (!cwd)
		return (NULL);
	// if (ft_strlen(cwd) == 1)
	// 	return(free(cwd), ft_strdup("/"));
	home = replace_env(data, ft_strdup("$HOME"));
	if (!home)
		return (free(cwd), NULL);
	home_len = ft_strlen(home);
	if (!ft_strncmp(cwd, home, home_len))
	{
		if (!cwd[home_len])
			dest = ft_strdup("~");
		else
			dest = ft_strjoin("~", ft_strdup(cwd + home_len));
	}
	else
		dest = ft_strdup(cwd);
	return (free(home), free(cwd), dest);
}
