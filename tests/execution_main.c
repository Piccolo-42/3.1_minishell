/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:05:30 by emurillo          #+#    #+#             */
/*   Updated: 2025/05/07 09:49:00 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// to compile use the following commands

// gcc -Wall -Wextra -Werror -Iinclude -Ilibft src/execution/*.c src/parsing/*.c src/builtins/ft*.c src/builtins/utils_bi.c src/utils_ms.c src/readline/*.c -lreadline -Llibft -lft -o test_execution

// int main(int argc, char **argv, char **envp)
// {
// 	t_data	data;

// 	(void)argc;
// 	(void)argv;
// 	data.envp = copy_envp(envp);
// 	data.exit_code = 0;
// 	while (1)
// 	{
// 		data.input = readline("minishell$ ");
// 		if (!data.input)
// 			break ;
// 		if (*data.input)
// 			add_history(data.input);
// 		data.ast = parsing(&data);
// 		if (data.ast)
// 			exec_pipeline(data.ast, &data);
// 		free_lst(&data.ast);
// 		free(data.input);
// 	}
// 	return (0);
// }
