/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:05:30 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/22 18:11:39 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// to compile use the following commands
//	gcc main_test.c exec_utils.c exec_pipe.c ../parsing/*.c ../utils_ms.c -lreadline -I../../include -I../../libft -L../../libft -lft -o test_main_with_parser

int main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	data.envp = copy_envp(envp);
	data.error = 0;
	while (1)
	{
		data.input = readline("minishell$ ");
		if (!data.input)
			break ;
		if (*data.input)
			add_history(data.input);
		data.ast = parsing(data.input);
		if (data.ast)
			exec_pipeline(data.ast, &data);
		free_lst(&data.ast);
		free(data.input);
	}
	return (0);
}
