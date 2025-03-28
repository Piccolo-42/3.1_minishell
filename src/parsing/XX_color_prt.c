/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XX_color_prt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 21:16:58 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/26 21:16:58 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prt_ast_colored(t_list *lst)
{
    int	i;
	int	lst_len;

    if (!lst)
		return ;
	check_print(lst);
	lst_len = lstlen(lst);
	i = 0;
    ft_printf("\n");
    while (lst)
    {
		prt_ast_content(lst, i, lst_len);
        lst = lst->next;
		i++;
    }
    ft_printf("\n\n\n");
    return;
}

void check_print(t_list *lst)
{
	int	i;

    if (!lst)
		return ;
	i = 0;
    while (lst)
    {
		if (lst->read && is_redir((lst->read)->type))
			set_rest_green(lst);
		if (lst->write && is_redir((lst->write)->type))
			set_rest_red(lst);
        lst = lst->next;
		i++;
    }
    return;

}

void	prt_ast_content(t_list *lst, int i, int lst_len)
{
	int n;

	if (lst->print == 0)
		printf("%s", RED);
	else
		printf("%s", GREEN);
	if (lst->type == PIPE)
		ft_printf("\n\t\t   %t | ", lst->type);
	else
	{
		prt_ast_read(lst, i);
		ft_printf("\n\t\t\t  %s", lst->content[0]);
		n = 1;
		while (lst->content[n])
			ft_printf(" \"%s\"", lst->content[n++]);
		prt_ast_write(lst, i, lst_len);
	}
	printf("%s", WHITE);
}

void	prt_ast_read(t_list *lst, int i)
{
	int		print;
	t_list	*read_node;

	print = 0;
	if (lst->read)
	{
		read_node = lst->read;
		if (!is_redir(read_node->type))
			ft_printf("\n\t\t\t \\ \n\t\t\t  \\");
		else
		{
			read_node->print = 1;
			ft_printf("\n\t\t\t   ");
		}
		while (read_node && is_redir(read_node->type))
		{
			ft_printf(" %s", read_node->content[0]);
			ft_printf("%s", read_node->content[1]);
			read_node = read_node->next;
			print = 1;
		}
		if (print)
			ft_printf("\n\t\t\t    /");
	}
	else if (!lst->read && i == 0)
		ft_printf("\n\t\t\t    <stdin\n\t\t\t    /");
	else
		ft_printf("\n\n");
}

void	prt_ast_write(t_list *lst, int i, int lst_len)
{
	t_list	*write_node;

	if (lst->write)
	{
		write_node = lst->write;
		if (!is_redir(write_node->type))
			ft_printf("\n\t\t\t  /\n\t\t\t /");
		else
			ft_printf("\n\t\t\t    \\ \n\t\t\t   ");
		while (write_node && is_redir(write_node->type))
		{
			ft_printf(" %s", write_node->content[0]);
			ft_printf("%s", write_node->content[1]);
			write_node = write_node->next;
		}
	}
	else if (!lst->write && i == lst_len - 1)
		ft_printf("\n\t\t\t    \\ \n\t\t\t    >stdout");
	else
		ft_printf("\n\n");
}

void	set_rest_red(t_list *lst)
{
	// t_list *branch;

	lst = lst->next;
	while (lst)
	{
		lst->print = 0;
		lst = lst->next;
	}
}

void	set_rest_green(t_list *lst)
{
	while (lst)
	{
		lst->print = 1;
		lst = lst->next;
	}
}
