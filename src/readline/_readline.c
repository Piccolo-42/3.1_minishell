/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _readline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:59:49 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/25 15:57:14 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_input(void)
{
	char	*input;
	char	*line;

	input = ft_calloc(1, 1);
	while (1)
	{
		line = readline(">: ");
		if (!line || !ft_strncmp(line, "exit", 4))
			return (free(input), NULL);
		input = ft_strjoin(input, line);
		if (!input)
			return (free(line), free(input), NULL);
		else if (last_char(line) != '|')
		{
			free(line);
			break ;
		}
		free(line);
	}
	return (input);
}
