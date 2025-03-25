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

int	main(void)
{
	char	*input;
	t_list	*ast;

	while (1)
	{
		input = read_input();
		if (!input)
			break ;
		if (*input)
			add_history(input);
		ast = parsing(input);
		prt_ast(ast);
		free_lst(&ast);

		//exe_cmd(ast)


		// more readline functions

		// Example of modifying input (replaces current line with "Modified Input")
		// rl_replace_line("Modified Input", 0);
		// rl_redisplay();
		// input = readline("Enter command2: ");
		// printf("mod: %s\n", input);
		// printf("\n");
	}
	rl_clear_history();
	return (0);
}
