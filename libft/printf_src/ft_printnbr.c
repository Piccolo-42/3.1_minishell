/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:42:53 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/23 15:42:53 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printnbr(int nbr)
{
	char	*str;
	int		count;

	str = ft_itoa(nbr);
	if (!str)
		return (0);
	count = ft_printstr(str);
	free(str);
	return (count);
}

int	ft_printunint(unsigned int nbr)
{
	char	*str;
	int		count;

	str = ft_unitoa(nbr);
	if (!str)
		return (0);
	count = ft_printstr(str);
	free(str);
	return (count);
}

int	ft_printhex(int nbr, char conv)
{
	char	*str;
	int		count;

	if (conv == 'x')
	{
		str = ft_itoa_to_base(nbr, "0123456789abcdef");
		if (!str)
			return (0);
	}
	else
	{
		str = ft_itoa_to_base(nbr, "0123456789ABCDEF");
		if (!str)
			return (0);
	}
	ft_printstr(str);
	count = ft_strlen(str);
	free(str);
	return (count);
}

int	ft_printhexptr(void *ptr)
{
	int			count;
	uintptr_t	address;
	char		*str;

	address = (uintptr_t) ptr;
	str = ft_itoa_to_base(address, "0123456789abcdef");
	if (!str)
		return (0);
	write(1, "0x", 2);
	count = ft_printstr(str) + 2;
	free(str);
	return (count);
}
