/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _readline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:59:49 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/07 10:35:21 by sravizza         ###   ########.fr       */
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
	char	*prompt_malloc;
	char	prompt_fixed[128];

	if (!data)
		return (NULL);
	prompt_malloc = prompt(data);
	if (!prompt_malloc || !data->has_envp)
		line = readline("minishell$");
	else
	{
		ft_strlcpy(prompt_fixed, prompt_malloc, 127);
		ft_free(&(prompt_malloc));
		line = readline(prompt_fixed);
	}
	if (!line)
	{
		ft_putendl_fd("exit", 2);
		silent_exit(data, 0);
		return (NULL);
	}
	return (line);
}
// if (!ft_strncmp(line, "exit", 4))
// 	return (ft_free(&line),  NULL); //ft_free(&(data->prompt)), 

//prints USER@cSESSION:CWD$
char	*prompt(t_data *data)
{
	char	*name;
	char	*session;
	char	*cwd;
	char	*dest;

	name = replace_env(data, ft_strdup("$USER"));
	if (!name)
		return (NULL);
	session = get_session(data);
	if (!session)
		return (ft_free(&(name)), NULL);
	cwd = get_cwd(data);
	if (!cwd)
		return (ft_free(&(name)), ft_free(&(session)), NULL);
	dest = custom_join(name, session, cwd);
	free(name);
	free(session);
	free(cwd);
	return (dest);
}
