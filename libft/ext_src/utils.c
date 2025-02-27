/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:17:49 by sravizza          #+#    #+#             */
/*   Updated: 2025/02/21 16:55:41 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_src/libft.h"

/**
 * @param str str in base 10
 * @return base 16
 */
int	ft_atoi_base16(const char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
		i += 2;
	while (str[i])
	{
		result *= 16;
		if (str[i] >= '0' && str[i] <= '9')
			result += str[i] - '0';
		else if (str[i] >= 'A' && str[i] <= 'F')
			result += str[i] - 'A' + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			result += str[i] - 'a' + 10;
		i++;
	}
	return (result);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return ;
}

/**
 * @brief counts number of "words" in str separated by c;
 * @return count
 */
int	ft_wordcount(char *str, char c)
{
	int			i;
	static int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == 0))
			count++;
		i++;
	}
	return (count);
}
