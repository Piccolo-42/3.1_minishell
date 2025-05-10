/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:36:02 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/10 11:03:14 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param i pointer on token length
 * @returns type of token
 */
t_type	get_type(char *input, int *i)
{
	if (input[*i] == '|')
		return ((*i)++, PIPE);
	if (input[*i] == '<' || input[*i] == '>')
		return (handle_redir(input, i));
	return (handle_words(input, i));
}

t_type	handle_redir(char *input, int *i)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			(*i) += 2;
			return (HEREDOC);
		}
		(*i)++;
		return (REDIR_IN);
	}
	else
	{
		if (input[*i + 1] == '>')
		{
			(*i) += 2;
			return (APPEND);
		}
		(*i)++;
		return (REDIR_OUT);
	}
	return (NONE);
}

t_type	handle_words(char *input, int *i)
{
	char	quote;

	while (input[*i] && !is_whitespace(input[*i])
		&& !char_is_operator(input[*i]))
	{
		if (input[*i] == '\"' || input[*i] == '\'')
		{
			quote = input[*i];
			(*i)++;
			while (input[*i] && input[*i] != quote)
				(*i)++;
			if (input[*i] != quote)
				return (RM);
		}
		(*i)++;
	}
	return (WORD);
}
