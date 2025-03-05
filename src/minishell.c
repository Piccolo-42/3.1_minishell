/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:09:51 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/05 13:51:18 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char	*input;
    t_list	*lst;

	lst = NULL;
	ft_printf("\n");
    while (1)
    {
        input = readline(">: ");
        if (!input || !ft_strncmp(input, "exit", 4))
            break;
        if (*input)
            add_history(input);
        // printf("input: %s\n", input);
        parsing(input, &lst);
		if (!lst)
			ft_printf("no list pointed\n");
		else
			prt_lst(lst);
        // Example of modifying input (replaces current line with "Modified Input")
        // rl_replace_line("Modified Input", 0);
        // rl_redisplay();
        // input = readline("Enter command2: ");
        // printf("mod: %s\n", input);
        // printf("\n");
    }
    rl_clear_history();
	free_lst(&lst);
    return 0;
}

int is_whitespace(char c)
{
	if (c == ' ' || (9 <= c && c <= 13))
		return (1);
	return (0);
}

int	len_crop(char *input, int len_token)
{
	int	i;

	i = len_token;
	while (input[i] && is_whitespace(input[i]))
		i++;
	return (i);
}
