/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:32:22 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/10 15:54:14 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief is  < << >> > ?
 */
int	is_redir(t_type	type)
{
	if (type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC)
		return (1);
	return (0);
}

int	is_operator(t_type type)
{
	if (is_redir(type) || type == PIPE)
		return (1);
	return (0);
}

int	char_is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	advance_quote(char *old, int i)
{
	char	quote;

	quote = old[i];
	i++;
	while (old[i] != quote)
		i++;
	i++;
	return (i);
}

int	count_split(char *old)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (old[i])
	{
		if (old[i] == '\'' || old[i] == '\"')
		{
			count++;
			i = advance_quote(old, i);
		}
		else
		{
			count++;
			while (old[i] && old[i] != '\'' && old[i] != '\"')
				i++;
			if (!old[i])
				break ;
		}
	}
	return (count);
}
