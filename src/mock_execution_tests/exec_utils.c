/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:25:47 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/05 15:29:02 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 *
 * @brief Simple version of the exec function, used to execute the comands, no built-ins added.
 * @param node The node command list structure
 * @param envp Environmment 
 *
 */
void	ft_exec_simple(t_list *node, char **envp)
{
	pid_t	pid = fork();

	if (pid == 0)
	{
		execvp(node->content[0], node->content);
		perror("excecvp");
		exit(1);
	}
	else
		wait(NULL);
}
