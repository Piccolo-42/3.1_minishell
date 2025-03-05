#include "minishell.c"

void	prt_lst(t_list *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->input)
			ft_printf("in: %s", lst->input);
		else
			ft_printf("error in");
		if (lst->type)
			ft_printf("type: %s", lst->type);
		else
			ft_printf("error type");
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
	dest->input = input;
	dest->next = NULL;
	dest->type = NULL;
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
