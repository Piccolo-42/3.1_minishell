/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:45:05 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/05 13:50:03 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prt_lst(t_list *lst)
{
	int	i;

	if (!lst)
		return ;
	i = 0;
	while (lst)
	{
		if (lst->content)
			ft_printf("%d: %s\n", i, lst->content);
		else
			ft_printf("no txt\n");
		i++;
		lst = lst->next;
	}
	return;
}

t_list	*new_node(char *content)
{
	t_list	*dest;

	dest = malloc(sizeof(t_list));
	if (!dest)
		return (0);
	dest->content = ft_strdup(content);
	dest->type = NONE;
	dest->next = NULL;
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
}

void	free_lst(t_list **lst)
{
	t_list	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		free(temp);
	}
	*lst = NULL;
	return ;
}

// int	ft_lstsize(t_list *lst)
// {
// 	int	size;

// 	if (!lst)
// 		return (0);
// 	size = 0;
// 	while (lst)
// 	{
// 		lst = lst->next;
// 		size++;
// 	}
// 	return (size);
// }
