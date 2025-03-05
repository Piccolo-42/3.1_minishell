/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:09:51 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/04 15:40:41 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char *input;

    while (1)
    {
        input = readline("Enter command: ");
        if (!input || !ft_strncmp(input, "exit", 4))
            break;

        if (*input)
            add_history(input);

        printf("You entered: %s\n", input);
        parsing(input);
        // Example of modifying input (replaces current line with "Modified Input")
        // rl_replace_line("Modified Input", 0);
        // rl_redisplay();
        // input = readline("Enter command2: ");
        // printf("mod: %s\n", input);
        // printf("\n");

        free(input);
    }

    rl_clear_history();
    return 0;
}