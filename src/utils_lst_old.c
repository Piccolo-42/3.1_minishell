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
	if (!lst)
		return ;
	// ft_printf("\nLIST OF COMMANDS\n");
	while (lst)
	{
		if (lst->input)
			ft_printf("txt: %s\n", lst->input);
		else
			ft_printf("no txt\n");
		if (lst->type)
			ft_printf("type: %s\n\n", lst->type);
		else
			ft_printf("no type\n\n");
		if (lst->next)
			lst = lst->next;
		else
			break;
	}
	return;
}

t_list	*new_node(char *input)
{
	t_list	*dest;

	dest = malloc(sizeof(t_list));
	if (!dest)
		return (0);
	dest->input = ft_strdup(input);
	// ft_printf("token: %s\n", dest->input);
	dest->next = NULL;
	dest->type = NULL;
	return (dest);
}

void	node_add_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	// ft_printf("token nab: %s\n", new->input);
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

int	ft_lstsize(t_list *lst)
{
	int	size;

	if (!lst)
		return (0);
	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
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
