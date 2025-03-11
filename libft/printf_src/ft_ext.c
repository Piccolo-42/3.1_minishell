/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ext.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:27:49 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/11 11:25:43 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// char	*get_type_word_arg(t_type type)
// {
// 	if (type == SNG_Q)
// 		return ("SNG_Q");
// 	if (type == DBL_Q)
// 		return ("DBL_Q");
// 	if (type == WORD)
// 		return ("WORD");
// 	if (type == FL)
// 		return ("FL");
// 	if (type == CMD)
// 		return ("CMD");
// 	if (type == ARG)
// 		return ("ARG");
// 	return ("UNKOWN");
// }

// char	*get_type_name(t_type type)
// {
// 	if (type == PIPE)
// 		return ("PIPE");
// 	if (type == REDIR_IN)
// 		return ("REDIR_IN");
// 	if (type == REDIR_OUT)
// 		return ("REDIR_OUT");
// 	if (type == APPEND)
// 		return ("APPEND");
// 	if (type == HEREDOC)
// 		return ("HEREDOC");
// 	if (type == ENV)
// 		return ("ENV");
// 	if (type == NONE)
// 		return ("NONE");
// 	if (type == RM)
// 		return ("RM"); 
// 	return (get_type_word_arg(type));
// }

int	ft_printtype(t_type type)
{
	const char *type_str[] = {
		"PIPE", "REDIR_IN", "REDIR_OUT", "APPEND", "HEREDOC",
		"CMD", "FL", "ARG", "ENV", "SNG_Q", "DBL_Q",
		"WORD", "RM", "NONE"
	};

	if (type < PIPE || type > NONE)
		return (ft_printstr("UNKNOWN"));
	return (ft_printstr((char *)type_str[type]));
}
