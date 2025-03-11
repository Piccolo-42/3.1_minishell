/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ext.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:27:49 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/11 09:36:24 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_type_word_arg(t_type type)
{
	if (type == SNG_Q)
		return ("SNG_Q");
	if (type == DBL_Q)
		return ("DBL_Q");
	if (type == WORD)
		return ("WORD");
	if (type == FL)
		return ("FL");
	if (type == CMD)
		return ("CMD");
	if (type == ARG)
		return ("ARG");
	return ("UNKOWN");
}

char	*get_type_name(t_type type)
{
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	if (type == REDIR_OUT)
		return ("REDIR_OUT");
	if (type == APPEND)
		return ("APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == ENV)
		return ("ENV");
	if (type == NONE)
		return ("NONE");
	if (type == RM)
		return ("RM"); 
	return (get_type_word_arg(type));
}

int		ft_printtype(t_type type)
{
	char	*dest;

	dest = get_type_name(type);
	ft_printstr(dest);
	return (ft_strlen(dest));
}
