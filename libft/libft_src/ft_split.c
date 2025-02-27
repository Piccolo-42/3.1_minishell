/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:28:50 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/15 12:29:04 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_all(char **dest)
{
	int	i;

	i = 0;
	while (dest[i])
	{
		free(dest[i]);
		i++;
	}
	free(dest);
}

static int	ft_wordcount(char const *str, char c)
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

static int	ft_split2(char const *str, char c, char **dest)
{
	int		start;
	int		end;
	int		i;

	i = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		start = i;
		while (str[i] != c && str[i])
			i++;
		if (str[i] == c || i > start)
		{
			end = i;
			*dest = ft_substr(str, start, end - start);
			if (!*dest)
				return (0);
			dest++;
		}
	}
	*dest = 0;
	return (1);
}

/**
 * @warning malloc
 */
char	**ft_split(char const *str, char c)
{
	char	**dest;

	if (!str)
		return (0);
	dest = malloc(sizeof(char *) * (ft_wordcount(str, c) + 1));
	if (!dest)
		return (0);
	if (!ft_split2(str, c, dest))
	{
		free_all(dest);
		return (0);
	}
	return (dest);
}

/*int main ()
{
	int i = 0;
	char	**dest = ft_split("xonextwoxthree", 'x');
	while (dest[i])
	{
		printf("%s\n", dest[i]);
		i++;
	}
	free_all(dest);
	return (0);
}*/
