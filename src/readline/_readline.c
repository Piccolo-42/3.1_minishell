/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _readline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:59:49 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/30 14:02:00 by sravizza         ###   ########.fr       */
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

char	*read_input(void)
{
	char	*line;


	line = readline(">: ");
	if (!line)
		return (NULL);
	if (!ft_strncmp(line, "exit", 4))
		return (free(line), NULL);

	return (line);
}
