/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:32:22 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/05 21:32:22 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char *value)
{
	if (!ft_strncmp(value, "|", 1))
		return (1);
	else if (!ft_strncmp(value, "<", 1))
		return (1);
	else if (!ft_strncmp(value, ">", 1))
		return (1);
	else if (!ft_strncmp(value, "<<", 2))
		return (1);
	else if (!ft_strncmp(value, ">>", 2))
		return (1);
	else
		return (0);
}

int is_whitespace(char c)
{
	if (c == ' ' || (9 <= c && c <= 13))
		return (1);
	return (0);
}

int	len_crop(char *input, int len_token)
{
	int	i;

	i = len_token;
	while (input[i] && is_whitespace(input[i]))
		i++;
	return (i);
}
