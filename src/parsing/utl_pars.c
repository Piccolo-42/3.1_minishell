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

/**
 * @warning malloc
 * @return str1 + str2
 */
char	*ft_strjoin_free_one(char *str1, char *str2)
{
	char	*dest;
	size_t	i;

	// if (!str1)
	// 	return (str2);
	dest = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!dest)
		return (0);
	i = 0;
	while (str1[i])
	{
		dest[i] = str1[i];
		i++;
	}
	i = 0;
	while (str2[i])
	{
		dest[ft_strlen(str1) + i] = str2[i];
		i++;
	}
	dest[ft_strlen(str1) + i] = 0;
	free(str1);
	return (dest);
}
