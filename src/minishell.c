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
	t_data	*data;

	(void)argc;
	(void)argv;
	if (!envp)
		exit_handler(data, "envp not set", 1);
	data = init_data(envp);
	if (!data)
		exit_handler(data, "memory allocation failed", 1);
	while (1)
	{
		data->input = read_input(data);
		if (!data->input)
			break ;
		if (*(data->input))
			add_history(data->input);
		data->ast = parsing(data);
		if (!data->ast)
			exit_handler(data, "memory allocation failed", 1);
		// ft_printf("EXE\n");
		// basic_prt_lst(data->ast);
		// prt_ast_colored(data->ast);
		// builtin_tester(&data);
		//exe_cmd(ast)
		if (data->ast)
			exec_pipeline(data->ast, data);
		free(data->input);
		data->input = NULL;
		free_lst(&(data->ast));
		data->ast = NULL;
	}
	exit_handler(data, NULL, 0);
	return (0);
}

// more readline functions

// Example of modifying input (replaces current line with "Modified Input")
// rl_replace_line("Modified Input", 0);
// rl_redisplay();
// input = readline("Enter command2: ");
// printf("mod: %s\n", input);
// printf("\n");
