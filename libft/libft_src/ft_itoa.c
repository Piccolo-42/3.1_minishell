/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:36:03 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/10 14:28:46 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbrlen(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

/**
 * @warning malloc
 */
char	*ft_itoa(int n)
{
	char	*dest;
	long	nbr;
	size_t	destlen;

	nbr = n;
	destlen = nbrlen(n);
	dest = malloc(sizeof(char) * (destlen + 1));
	if (!dest)
		return (0);
	if (nbr == 0)
		dest[0] = '0';
	if (nbr < 0)
	{
		dest[0] = '-';
		nbr = -nbr;
	}
	dest[destlen] = 0;
	while (nbr > 0)
	{
		dest[destlen -1] = 48 + (nbr % 10);
		nbr /= 10;
		destlen--;
	}
	return (dest);
}
