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
		return (1);
	data = init_data(envp);
	if (!data)
		return (1);
	while (1)
	{
		data->input = read_input(data);
		if (!data->input)
			break ;
		if (*(data->input))
			add_history(data->input);
		data->ast = parsing(data);
		if (!data->ast)
			return (1); //free
		// prt_ast_colored(data->ast);
		builtin_tester(&data);
		//exe_cmd(ast)
		// ft_printf("EXE\n");
		// basic_prt_lst(data->ast);
		free(data->input);
		free_lst(&(data->ast));
	}
	rl_clear_history();
	free_double(data->envp);
	free(data);
	return (0);
}

// more readline functions

// Example of modifying input (replaces current line with "Modified Input")
// rl_replace_line("Modified Input", 0);
// rl_redisplay();
// input = readline("Enter command2: ");
// printf("mod: %s\n", input);
// printf("\n");