/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:45:05 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/10 15:17:58 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*new_node(char *token, t_type ttype)
{
	t_list	*dest;

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
	dest->prev = NULL;
	dest->next = NULL;
	dest->read = NULL;
	dest->write = NULL;
	return (dest);
}

void	node_add_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

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
		return (void)free(new_content);
	new_content[i + 1] = NULL;
	free(node->content);
	node->content = new_content;
}

void	remove_node(t_list **lst, t_list **node)
{
	t_list	*remove;
	t_list	*next;

	if (!*node)
		return ;
	remove = *node;
	next = (*node)->next;
	if (remove->prev)
		(remove->prev)->next = next;
	else
		*lst = next;
	if (next)
		next->prev = remove->prev;
	free_double(remove->content);
	free(remove);
	*node = next;
	return ;
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

//stack overflow
void	free_lst(t_list **lst)
{
	t_list	*node;
	t_list	*next;

	if (!lst || !*lst)
		return ;
	node = *lst;
	while (node)
	{
		next = node->next;
		free_lst_redir(node);
		free_double(node->content);
		free(node);
		node = next;
	}
	*lst = NULL;
	return ;
}

void	free_lst_redir(t_list *node)
{
	// t_list	*temp;
	// t_list	*next;

	if (!node)
		return ;
	// if (node->read)
	// {
	// 	temp = node->read;
	// 	while (temp)
	// 	{
	// 		next = temp->next;
	// 		if (temp->content)
	// 			free_double(temp->content);
	// 		free(temp);
	// 		temp = next;
	// 	}
	// 	node->read = NULL;
	// }
	// if (node->write)
	// {
	// 	temp = node->write;
	// 	while (temp)
	// 	{
	// 		next = temp->next;
	// 		if (temp->content)
	// 			free_double(temp->content);
	// 		free(temp);
	// 		temp = next;
	// 	}
	// 	node->write = NULL;
	// }
}
