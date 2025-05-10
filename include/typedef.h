/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:24:19 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/10 10:54:33 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H
# include "minishell.h"

typedef enum e_type
{
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	CMD,
	FIL,
	ARG,
	ENV,
	SNG_Q,
	DBL_Q,
	WORD,
	RM,
	NONE,
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

typedef struct s_data
{
	char	**envp;
	char	*input;
	t_list	*ast;
	int		prt;
	char	*prompt;
	int		has_envp;
	int		here_doc;
	int		expand_here_doc;
	int		c_stdin;
	int		c_stdout;
}	t_data;

typedef struct s_exec_ctx
{
	int		i;
	int		n_cmd;
	int		n_pipe;
	t_list	*node;
	int		*pipe_fd;
	t_data	*data;
}	t_exec_ctx;

#endif
