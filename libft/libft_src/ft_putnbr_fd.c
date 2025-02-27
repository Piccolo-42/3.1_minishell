/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:29:46 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/14 18:03:54 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *str, int fd);

static void	ft_recursive(int n, int fd)
{
	char	temp;

	if (n >= 10)
		ft_recursive(n / 10, fd);
	temp = '0' + (n % 10);
	write(fd, &temp, 1);
	return ;
}

void	ft_putnbr_fd(int nbr, int fd)
{
	if (nbr == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr = -nbr;
	}
	ft_recursive(nbr, fd);
	return ;
}
/*
int	main(void)
{
	ft_putnbr_fd(42, 1);
	write(1, "\n", 1);
	return (0);
}
*/