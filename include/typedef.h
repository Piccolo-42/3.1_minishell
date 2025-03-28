/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:24:19 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/25 11:25:23 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H
# include "minishell.h"

typedef enum e_type
{
	PIPE,		// |
	REDIR_IN,	// <
	REDIR_OUT,	// >
	APPEND,		// >>
	HEREDOC,	// <<
	CMD,		// command
	FIL,		// file
	ARG,		// arguments and flags
	ENV,		// $ENV
	SNG_Q,		// quotes ''
	DBL_Q,		// quotes ""
	WORD,		// undefined yet
	RM,			// solitary quotes to remove
	NONE,		// default, not assigned yet
}	t_type;

typedef struct s_list
{
	char			**content;
	t_type			type;
	t_type			subtype;
	int				print;
	struct s_list	*prev;
	struct s_list	*next;
	struct s_list	*read;
	struct s_list	*write;
}	t_list;

#endif
