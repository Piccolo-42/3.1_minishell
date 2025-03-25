/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:07:20 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/25 11:21:26 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	last_char(char *str)
{
	int		i;
	char	last;

	i = 0;
	last = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i]))
			last = str[i];
		i++;
	}
	return (last);
}
