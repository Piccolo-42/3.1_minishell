/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:07:32 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/05 16:24:40 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

t_ast	*new_node(char *input)
{
	t_ast	*dest;

	dest = malloc(sizeof(t_ast));
	if (!dest)
		return (NULL);
	dest->value = ft_strdup(input);
	dest->type = NULL;
	dest->left = NULL;
	dest->right = NULL;
	dest->args = NULL;
	return (dest);
}

void	add_args_to_node(t_ast **ast, t_ast *arg)
{
	t_ast	*tmp;

	// ft_printf("token nab: %s\n", new->input);
	if (!*ast)
	{
		*ast = arg;
		return ;
	}
	tmp = *ast;
	while (tmp->args)
		tmp = tmp->args;
	tmp->args = arg;
	return ;
}
