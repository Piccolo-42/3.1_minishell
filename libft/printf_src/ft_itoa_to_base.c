/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_to_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:40:34 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/23 17:40:34 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_nbrlen_base(long nbr, int basesize)
{
	int	nbrsize;

	nbrsize = 0;
	if (nbr < 0)
		nbrsize++;
	while (nbr != 0)
	{
		nbr = nbr / basesize;
		nbrsize++;
	}
	return (nbrsize);
}

char	*ft_recursive(long nbr, char *base, char *dest, int i)
{
	int		basesize;

	basesize = ft_strlen(base);
	if (nbr >= basesize)
		ft_recursive(nbr / basesize, base, dest, i - 1);
	dest[i] = base[(nbr % basesize)];
	return (dest);
}

char	*ft_itoa_to_base(long nbr, char *base)
{
	int		basesize;
	char	*dest;
	int		nbrsize;

	basesize = ft_strlen(base);
	nbrsize = ft_nbrlen_base(nbr, basesize);
	dest = malloc(sizeof(char) * nbrsize + 1);
	if (nbr < 0)
	{
		nbr = -nbr;
		dest[0] = '-';
	}
	dest[nbrsize] = 0;
	return (ft_recursive(nbr, base, dest, nbrsize - 1));
}
