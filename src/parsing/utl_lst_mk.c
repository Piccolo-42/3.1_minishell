/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_lst_mk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:45:05 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/25 16:15:45 by sravizza         ###   ########.fr       */
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

	i = 0;
	type = get_type(input, &i);
	token = ft_substr(input, 0, i);
	if (!token)
		return (0);
	node_add_back(lst, new_node(token, type));
	free(token);
	return (i);
}

t_list	*new_node(char *token, t_type ttype)
{
	t_list	*dest;

	if (!token || !*token)
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

void	add_arg(t_list *node, char *arg)
{
	int		i;
	char	**new_content;

	if (!node || !arg)
		return ;
	i = 0;
	while (node->content[i])
		i++;
	new_content = malloc(sizeof(char *) * (i + 2));
	if (!new_content)
		return ;
	i = 0;
	while (node->content[i])
	{
		new_content[i] = node->content[i];
		i++;
	}
	new_content[i] = ft_strdup(arg);
	if (!new_content[i])
		return ((void)free(new_content));
	new_content[i + 1] = NULL;
	free(node->content);
	node->content = new_content;
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
