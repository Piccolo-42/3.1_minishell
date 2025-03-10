/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:36:02 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/07 14:36:02 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	handle_quotes(char *input, int *i)
{
	char	quote;
	int		start;

	start = *i;
	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
	{
		*i = start + 1;
		return (RM);
	}
	(*i)++;
	if (input[*i - 1] == '\"')
		return (DBL_Q);
	if (input[*i - 1] == '\'')
		return (SNG_Q);
	return (WORD);
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

t_type	handle_env(char *input, int *i)
{
	(*i)++;
	while (input[*i] && !is_whitespace(input[*i])
		&& input[*i] != '<' && input[*i] != '>'
		&& input[*i] != '|' && input[*i] != '$'
		&& input[*i] != '\'' && input[*i] != '\"')
	{
		(*i)++;
	}
	return (ENV);
}

t_type	handle_words(char *input, int *i)
{
	while (input[*i] && !is_whitespace(input[*i])
		&& input[*i] != '<' && input[*i] != '>'
		&& input[*i] != '|' && input[*i] != '$'
		&& input[*i] != '\'' && input[*i] != '\"')
	{
		(*i)++;
	}
	return (WORD);
}

// t_type	handle_pipe(int	*i)
// {
// 	(*i)++;
// 	return (PIPE);
// }
