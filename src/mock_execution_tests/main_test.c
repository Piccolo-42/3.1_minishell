/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:19:21 by emurillo          #+#    #+#             */
/*   Updated: 2025/04/07 14:29:57 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_data	data;

	void(argc);
	void(argv);
	data.envp = copy_envp(envp);
	data.error = 0;
	while (1)
	{
		data.input = readline("minishell$ ");
		if (!data.input)
			break ;
		if (*data.input)
			add_history(data.input)
	}
}
