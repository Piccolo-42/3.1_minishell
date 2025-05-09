/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:05:15 by emurillo          #+#    #+#             */
/*   Updated: 2025/05/02 18:10:31 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// to compile use the following commands

// gcc -Wall -Wextra -Werror -Iinclude -Ilibft  src/execution/*.c src/parsing/*.c src/builtins/ft*.c src/builtins/utils_bi.c src/utils_ms.c src/readline/*.c -lreadline -Llibft -lft -o test_execution

/* int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;

	(void)argc;
	(void)argv;
	data.envp = copy_envp(envp);
	data.exit_code = 0;
	if (!isatty(STDIN_FILENO))
	{
		line = get_next_line(STDIN_FILENO);
		while (line)
		{
			data.input = line;
			data.ast = parsing(&data);
			if (data.ast)
				exec_pipeline(data.ast, &data);
			free_lst(&data.ast);
			free(data.input);
			line = get_next_line(STDIN_FILENO);
		}
	}
	return (0);
} */
