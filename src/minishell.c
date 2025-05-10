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
	data = init_data(envp);
	if (!data)
		exit_handler(NULL, "data: memory allocation failed", 1);
	while (1)
	{
		data->here_doc = 0;
		signal_init(data);
		data->input = read_input(data);
		if (!data->input)
			break ;
		if (*(data->input))
			execution(data);
		ft_free(&(data->input));
	}
	exit_handler(data, NULL, g_exit_code);
	return (0);
}

void	execution(t_data *data)
{
	add_history(data->input);
	data->ast = parsing(data);
	if (data->ast)
	{
		data->prt = 1;
		exec_pipeline(data->ast, data);
	}
	free_heredocs(data->ast);
	free_lst(&(data->ast));
}

// basic_prt_lst(data->ast);
