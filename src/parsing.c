/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:11:42 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/05 13:33:50 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ast_build(t_list **plst, t_ast **ast)
{
	t_list	*lst;

	lst = *plst;
	while (lst)
	{
		if (!ft_strncmp(lst->content, "|", 1))
			*ast = new_ast_node(lst->content, PIPE); 
		
		
		lst = lst->next;
	}

}

void	parsing(char *input, t_ast *ast)
{
	t_list	*lst;

	lst = NULL;
	tokenisation(input, &lst);
	if (!lst)
		ft_printf("no list pointed\n");
	else
		prt_lst(lst);
	ast_build(&lst, &ast);
    free_lst(&lst);
	
	return ;
}

void	tokenisation(char *input, t_list **lst)
{
	char	*token;
	char	*leftover;
	int		left_len;
	int		left_start;

	token = get_token(input);
	if (!token)
		return ;
	node_add_back(lst, new_node(token));
	left_start = len_crop(input, ft_strlen(token));
	left_len = ft_strlen(input) - left_start;
	leftover = ft_substr(input, left_start, left_len);
	free(input);
	free(token);
	if (*leftover)
		return (tokenisation(leftover, lst));
	free(leftover);
	return ;
}

char	*get_token(char *input)
{
	int	i;
	int	start;

	i = 0;
	while (input[i])
	{
		while (is_whitespace(input[i]))
			i++;
		if (input[i] == '\"')
		{
			// ft_printf("entering doublequote loop\n");
			start = i;
			i++;
			while (input[i] && input[i] != '\"')
				i++;
			if (input[start] == '\"' && input[i] == '\"')
				return (ft_substr(input, start, i - start + 1));
			else
				i = start++;
			// ft_printf("quote len: %d\n", i - 1);
		}
		if (input[i] == '\'')
		{
			start = i;
			i++;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[start] == '\'' && input[i] == '\'')
				return (ft_substr(input, start, i - start + 1));
			else
				i = start++;
		}
		if (input[i] == '<' || input[i] == '>' ||  input[i] == '|')
			return (ft_substr(input, i, 1));
		if (input[i] == '<' && input[i+1] && input[i + 1] == '<')
			return (ft_substr(input, i , 2));
		if (input[i] == '>' && input[i+1] && input[i + 1] == '>')
			return (ft_substr(input, i , 2));
		if (input[i] == '$')
		{
			start = i;
			i++;
			while (input[i] && ft_isalnum(input[i]))
				i++;
			return (ft_substr(input, start, i - start));
		}
		if (ft_isalnum(input[i]))
		{
			start = i;
			while (ft_isalnum(input[i]))
				i++;
			return (ft_substr(input, start , i - start));
		}
	}
	return (NULL);
}
