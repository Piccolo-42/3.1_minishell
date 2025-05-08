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
	// if (!envp)
	// 	exit_handler(NULL, "envp not set", 1);
	//	envp = NULL;
	data = init_data(envp);
	if (!data)
		exit_handler(NULL, "data: memory allocation failed", 1);
	while (1)
	{
		signal_init(data);
		data->input = read_input(data);
		if (!data->input)
			break ;
		if (*(data->input))
		{
			add_history(data->input);
			data->ast = parsing(data);
			if (!data->ast && data->prt)
				/*error_handler("ast: memory allocation failed", 1)*/;
			else
			{
				data->prt = 1;
				// basic_prt_lst(data->ast);
				// prt_ast_colored(data->ast);
				// builtin_tester(&data);
			 	exec_pipeline(data->ast, data);
				free_lst(&(data->ast));
			}
		}
		ft_free(&(data->input));
	}
	exit_handler(data, NULL, g_exit_code);
	return (0);
}

// more readline functions

// Example of modifying input (replaces current line with "Modified Input")
// rl_replace_line("Modified Input", 0);
// rl_redisplay();
// input = readline("Enter command2: ");
// printf("mod: %s\n", input);
// printf("\n");
