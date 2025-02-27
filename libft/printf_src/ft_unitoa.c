/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:13:46 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/25 15:13:46 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

char	*ft_unitoa(unsigned int n)
{
	char			*dest;
	unsigned long	nbr;
	size_t			destlen;

	nbr = n;
	destlen = nbrlen(n);
	dest = malloc(sizeof(char) * (destlen + 1));
	if (!dest)
		return (0);
	if (nbr == 0)
		dest[0] = '0';
	dest[destlen] = 0;
	while (nbr > 0)
	{
		dest[destlen -1] = 48 + (nbr % 10);
		nbr /= 10;
		destlen--;
	}
	return (dest);
}
