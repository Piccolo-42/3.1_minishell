/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:09:51 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/10 15:57:08 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	// char	*input;
	// t_list	*ast;
	// int		exit_status;
	t_data	*data;

	(void)argc;
	(void)argv;
	// (void)envp;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->envp = copy_envp(envp);
	if (!data->envp)
		return (free(data), 1);
	// mini_unset(&data->envp,"_");
	while (1)
	{
		data->input = read_input();
		if (!data->input)
			break ;
		if (*(data->input))
			add_history(data->input);
		data->ast = parsing(data->input);
		if (!data->ast)
			return (1); //free
		// prt_ast_colored(data->ast);
		builtin_tester(&data);
		//exe_cmd(ast)
		
		free_lst(&(data->ast));
	}
	rl_clear_history();
	return (0);
}

// more readline functions

// Example of modifying input (replaces current line with "Modified Input")
// rl_replace_line("Modified Input", 0);
// rl_redisplay();
// input = readline("Enter command2: ");
// printf("mod: %s\n", input);
// printf("\n");