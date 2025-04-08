/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:25:47 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/08 17:24:34 by emurillo         ###   ########.fr       */
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
		execvp(node->content[0], node->content);
		perror("excecvp");
		exit(1);
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
		if (node->type == CMD && node->next && node->next->type == PIPE)
		{
			ft_exec_pipe(node, node->next->next, data->envp);
			node = node->next->next;
		}
		if (node->type == CMD)
		{
			ft_exec_simple(node, data->envp);
		}
		node = node->next;
	}
}

void	ft_exec_pipe(t_list *left, t_list *right, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return ;
	}
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execvp(left->content[0], left->content);
		perror("execvp left");
		exit(1);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		execvp(right->content[0], right->content);
		perror("execvp left");
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
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

