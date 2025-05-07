/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:21:17 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/05 15:26:33 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exec_ast(t_data *data)
{
	t_list *node;

	node = data->ast;

	while (node)
	{
		if (node->type == CMD)
		{
			ft_exec_simple()
		}
	}
}
