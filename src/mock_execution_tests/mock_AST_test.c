/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_AST_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:03:42 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/22 17:58:37 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/**
 * @brief creates a mock AST to check the functionality of our structure.
 *
**/
t_list	*mock_ast_ls_la(void)
{
	t_list	*cmd = malloc(sizeof(t_list));

	cmd->type = CMD;
	cmd->content = ft_split("ls -la", ' ');
	cmd->read = NULL;
	cmd->write = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}


void	ft_exec_mock_cmd(t_list *node, char **envp)
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

int	main(int argc, char **argv, char **envp)
{
	t_list *ast = mock_ast_ls_la();
	ft_exec_mock_cmd(ast, envp);
	return (0);
}
