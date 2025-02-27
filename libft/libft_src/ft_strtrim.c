/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:43:39 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/15 18:38:21 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*getstart(char const *str, char const *set)
{
	size_t	i;
	size_t	j;
	int		setbool;

	i = 0;
	while (str[i])
	{
		setbool = 0;
		j = 0;
		while (set[j])
		{
			if (str[i] == set[j])
				setbool = 1;
			j++;
		}
		if (!setbool)
			break ;
		i++;
	}
	return ((char *) str + i);
}

static char	*getend(char const *str, char const *set, char const *start)
{
	size_t	i;
	size_t	j;
	int		setbool;

	i = ft_strlen(str) - 1;
	while (str + i >= start)
	{
		setbool = 0;
		j = 0;
		while (set[j])
		{
			if (str[i] == set[j])
				setbool = 1;
			j++;
		}
		if (!setbool)
			break ;
		i--;
	}
	if (str + i < start)
		return ((char *) start);
	return ((char *) str + i);
}

static char	*trim2(char const *start, char const *end)
{
	char	*dest;
	size_t	i;

	dest = malloc(sizeof(char) * (end - start + 2));
	if (!dest)
		return (0);
	i = 0;
	while (start + i <= end)
	{
		dest[i] = start[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * @brief (set) old_str (set)
 * @returns new_str
 * @warning malloc
 */
char	*ft_strtrim(char const *str, char const *set)
{
	char	*start;
	char	*end;
	char	*dest;

	start = getstart(str, set);
	end = getend(str, set, str);
	if (!str || end < start)
	{
		dest = malloc(sizeof(char) * 1);
		if (!dest)
			return (0);
		dest[0] = 0;
	}
	else
		dest = trim2(start, end);
	if (!dest)
		return (0);
	return (dest);
}
