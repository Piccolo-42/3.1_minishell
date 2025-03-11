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
 * @brief is space or whitespace (9-13 incl)
 */
int	is_whitespace(char c)
{
	if (c == ' ' || (9 <= c && c <= 13))
		return (1);
	return (0);
}

/**
 * @brief is  < << >> > ?
 */
int	is_redir(t_type	type)
{
	if (type == REDIR_IN || type == REDIR_OUT || type == APPEND || type == HEREDOC)
		return (1);
	return (0);
}

int	is_operator(t_type type)
{
	if (is_redir(type) || type == PIPE)
		return (1);
	return (0);
}
