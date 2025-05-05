/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ext.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:27:49 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/04 10:40:14 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printtype(t_type type)
{
	const char	*type_str[] = {
		"PIPE", "REDIR_IN", "REDIR_OUT", "APPEND", "HEREDOC",
		"CMD", "FIL", "ARG", "ENV", "SNG_Q", "DBL_Q",
		"WORD", "RM", "NONE"
	};

	if (type < PIPE || type > NONE)
		return (ft_printstr("UNKNOWN"));
	return (ft_printstr((char *)type_str[type]));
}
