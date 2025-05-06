/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_lst_mk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:45:05 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/06 14:15:33 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief *char to t_list node 
 * @returns strlen(token)
 */
int	create_token(char *input, t_list **lst)
{
	int		i;
	t_type	type;
	char	*token;
	t_list	*node;

	i = 0;
	type = get_type(input, &i);
	token = ft_substr(input, 0, i);
	if (!token)
		return (error_handler("ast: token: memory allocation failed", 1), -1);
	node = new_node(token, type);
	if (!node)
		return (error_handler(
				"ast: new_node: memory allocation failed", 1), -1);
	free(token);
	node_add_back(lst, node);
	return (i);
}

t_list	*new_node(char *token, t_type ttype)
{
	t_list	*dest;

	if (!token) // || !*token)
		return (NULL);
	dest = malloc(sizeof(t_list));
	if (!dest)
		return (NULL);
	dest->content = malloc(sizeof(char *) * 2);
	if (!dest->content)
		return (free(dest), NULL);
	dest->content[0] = ft_strdup(token);
	if (!(dest->content[0]))
		return (free(dest->content), free(dest), NULL);
	dest->content[1] = NULL;
	dest->type = ttype;
	dest->subtype = NONE;
	dest->print = 1;
	dest->prev = NULL;
	dest->next = NULL;
	dest->read = NULL;
	dest->write = NULL;
	return (dest);
}

void	node_add_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

int	add_arg(t_list *node, char *arg)
{
	int		i;
	char	**new_content;

	if (!node || !arg)
		return (0);
	i = 0;
	while (node->content[i])
		i++;
	new_content = malloc(sizeof(char *) * (i + 2));
	if (!new_content)
		return (error_handler("ast: arg: memory allocation failed", 1), 0);
	i = 0;
	while (node->content[i])
	{
		new_content[i] = node->content[i];
		i++;
	}
	new_content[i] = ft_strdup(arg);
	if (!new_content[i])
		return (error_handler(
				"ast: arg: memory allocation failed", 1), free(new_content), 0);
	new_content[i + 1] = NULL;
	free(node->content);
	node->content = new_content;
	return (1);
}

int	lstlen(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
