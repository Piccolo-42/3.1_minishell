/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:54:12 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/23 16:54:12 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include "../libft_src/libft.h"

int		ft_printf(const char *format, ...);
int		ft_conversion(va_list args, char conv);
int		ft_printchar(int c);
int		ft_printstr(char *str);
int		ft_printhexptr(void *ptr);
int		ft_printnbr(int nbr);
int		ft_printunint(unsigned int nbr);
int		ft_printhex(int nbr, char conv);
char	*ft_itoa_to_base(long nbr, char *base);
char	*ft_unitoa(unsigned int n);

#endif