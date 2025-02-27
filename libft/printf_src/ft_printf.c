/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:12:54 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/18 16:12:54 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_conversion(va_list args, char conv);
int	ft_printchar(int c);
int	ft_printstr(char *str);

/**
 * @brief s str | di nbr | p ptr | xX hex | c char | % % 
 * @return total count of print
 */
int	ft_printf(const char *format, ...)
{
	int		count;
	int		i;
	va_list	args;

	if (!format)
		return (0);
	count = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += ft_conversion(args, format[i + 1]);
			i++;
		}
		else
			count += ft_printchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}

int	ft_conversion(va_list args, char conv)
{
	if (conv == 'c')
		return (ft_printchar(va_arg(args, int)));
	else if (conv == 's')
		return (ft_printstr(va_arg(args, char *)));
	else if (conv == 'p')
		return (ft_printhexptr(va_arg(args, void *)));
	else if (conv == 'd' || conv == 'i')
		return (ft_printnbr(va_arg(args, int)));
	else if (conv == 'u')
		return (ft_printunint(va_arg(args, unsigned int)));
	else if (conv == 'x' || conv == 'X')
		return (ft_printhex(va_arg(args, int), conv));
	else if (conv == '%')
		return (ft_printchar('%'));
	return (0);
}

int	ft_printchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_printstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_printchar(str[i]);
		i++;
	}
	return (i);
}

/*int	main(void)
{
	//char	*str;

	//printf("og: %s %u Haricots à %p \n\n", "Je mange", -42, str);
	//ft_printf("ft: %s %u Haricots à %p \n\n", "Je mange", -42, str);

	//printf("\n");

	//printf("");
	//ft_printf("");

	//ft_printf("\n");

	printf("og: 42 = %x\n", -42);
	ft_printf("ft: 42 = %x\n", -42);

	//printf("\n", "Je mange", 42, str);
	//ft_printf("\n", "Je mange", 42, str);
	return (0);
}*/