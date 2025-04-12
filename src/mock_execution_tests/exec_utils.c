/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:25:47 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/09 14:24:51 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	ft_exec_pipe(t_list *left, t_list *right, char **envp);
void	ft_exec_simple(t_list *node, char **envp);

/**
 * @brief Executes a single command using execvp in a child process.
 *
 * This function forks a new process. In the child process, it attempts
 * to execute the command stored in the `node->content` array using `execvp`.
 * If the execution fails, it prints an error and exits. The parent process
 * waits for the child to finish before returning.
 *
 * @param node A pointer to a t_list node containing the command and its arguments.
 * @param envp A pointer to the environment variable array.
 */
void	ft_exec_simple(t_list *node, char **envp)
{
	pid_t	pid = fork();

	if (pid == 0)
	{
		//this is to be removed, only checks the arguments when one CMD is given.
		int	j = 0;
		while (node->content[j])
		{
			ft_printf("arg[%d]: %s\n", j, node->content[j]);
			j++;
		}
		execvp(node->content[0], node->content);
		perror("excecvp");
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}

/**
 * @brief Iterates through the AST and executes each CMD node.
 *
 * This function walks through the AST linked list and, for every node
 * of type CMD, it calls `ft_exec_simple()` to execute the command.
 * Currently, it does not handle pipes, redirections, or built-ins.
 *
 * @param data A pointer to the global t_data structure containing the AST and environment.
 */
void	ft_exec_ast(t_data *data)
{
	t_list *node = data->ast;

	while (node)
	{
		if (node->type == CMD && node->next && node->next->type == PIPE &&
			node->next->next && node->next->next->type == CMD)
		{
			ft_exec_pipes(node, node->next->next, data->envp);
			node = node->next->next->next;
		}
		else if (node->type == CMD)
		{
			ft_exec_simple(node, data->envp);
			node = node->next;
		}
		else
			node = node->next;
	}
}

/**
 * @brief Prints the structure of the AST to the terminal.
 *
 * This function iterates through the linked list representation of the AST,
 * and for each node, prints its index, type, and content (if available).
 * Useful for debugging and visualizing how the input command is parsed.
 *
 * @param lst Pointer to the head of the AST (linked list of t_list nodes).
 */
void	prt_ast(t_list *lst)
{
	int i = 0;

	while (lst)
	{
		printf("Node %d:\n", i);
		printf("  Type: %d\n", lst->type);
		if (lst->content)
		{
			int j = 0;
			while (lst->content[j])
			{
				printf("    content[%d]: %s\n", j, lst->content[j]);
				j++;
			}
		}
		lst = lst->next;
		i++;
	}
}

