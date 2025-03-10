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

#include "libft.h"

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

int	is_whitespace(char c)
{
	if (c == ' ' || (9 <= c && c <= 13))
		return (1);
	return (0);
}

/**
 * @brief crops all whitespaces from str, frees old str
 * @param crop 0 for front, 1 for back, 2 for both
 * @return new cropped string
 * @warning malloc
 */
char	*crop_whitespace(char *str, int crop)
{
	int		start;
	int		end;
	char	*dest;

	if (!str || crop < 0 || crop > 2)
		return (NULL);
	start = 0;
	if (crop == 0 || crop == 2)
	{
		while (str[start] && is_whitespace(str[start]))
			start++;
	}
	end = ft_strlen(str) - 1;
	if (crop == 1 || crop == 2)
	{
		while (end >= start && is_whitespace(str[end]))
			end--;
	}
	if (end < start)
		return (free(str), ft_strdup(""));
	dest = ft_substr(str, start, end - start + 1);
	if (!dest)
		return (NULL);
	free(str);
	return (dest);
}
