/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:19:21 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/08 17:01:57 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// to compile use the following commands
//	gcc main_test.c exec_utils.c ../parsing/*.c ../utils_ms.c -lreadline -I../../include -I../../libft -L../../libft -lft -o test_main_with_parser


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
		prt_ast(data.ast);
		ft_exec_ast(&data);
		free_lst(&data.ast);
		free(data.input);
	}
	return (0);
}
