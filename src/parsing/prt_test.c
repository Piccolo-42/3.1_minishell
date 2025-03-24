/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zgeg.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:15:58 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/10 17:43:14 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// <infile grep hello | grep world | wc -l >outfile
// <in1   grep <    in2<in3 hello     <in4 >out1| grep world |<in5      wc -l >out2>out3

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
			ft_printf("\n\t\t\t   ");
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

void	prt_ast_content(t_list *lst, int i, int lst_len)
{
	int n;

	if (lst->type == PIPE)
		ft_printf("\n\t\t   %t | ", lst->type);
	else
	{
		prt_ast_read(lst, i);
		ft_printf("\n\t\t\t  %s", lst->content[0]);
		n = 1;
		while (lst->content[n])
			ft_printf(" %s", lst->content[n++]);
		prt_ast_write(lst, i, lst_len);
	}
}

void	prt_ast(t_list *lst)
{
    int	i;
	int	lst_len;

    if (!lst)
		return ;
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

// void prt_lst(t_list *lst)
// {
//     int n;

//     if (!lst)
//         return;
//     ft_printf("\n");
//     while (lst)
//     {
//         // Print the main command/token
//         ft_printf("\t\t\t  %s", lst->content[0]);
//         ft_printf(" (%t)", lst->type);
//         if (lst->subtype == DBL_Q || lst->subtype == SNG_Q)
//             ft_printf(", (%t)", lst->subtype);
        
//         // Print arguments if any
//         if (lst->content[1])
//             ft_printf("\n\t\t\t\targs:");
//         n = 1;
//         while (lst->content[n])
//             ft_printf(" \"%s\"", lst->content[n++]);
        
//         // Print read redirections if any
//         if (lst->read)
//         {
//             t_list *read_node = lst->read;
// 			ft_printf("\n\t\t\t\tread:");
// 			ft_printf(" %s", read_node->content[0]);
//             if (read_node && is_redir(read_node->type))
// 				ft_printf("%s", read_node->content[1]);
// 			read_node = read_node->next;
//             while (read_node && is_redir(read_node->type))
//             {
// 				ft_printf(" %s", read_node->content[0]);
// 				ft_printf("%s", read_node->content[1]);
//                 read_node = read_node->next;
//             }
//         }
        
//         // Print write redirections if any
//         if (lst->write)
//         {
//             t_list *write_node = lst->write;
//             ft_printf("\n\t\t\t\twrite:");
// 			ft_printf(" %s", write_node->content[0]);
// 			if (write_node && is_redir(write_node->type))
// 				ft_printf("%s", write_node->content[1]);
//             write_node = write_node->next;
//             while (write_node && is_redir(write_node->type))
//             {
// 				ft_printf(" %s", write_node->content[0]);
// 				ft_printf("%s", write_node->content[1]);
//                 write_node = write_node->next;
//             }
//         }
        
//         ft_printf("\n");
// 		ft_printf("\n");
//         lst = lst->next;
//     }
//     ft_printf("\n");
//     return;
// }

void	rev_prt_lst(t_list *lst)
{
    // t_list  *arg;
    int     n;

    if (!lst)
        return ;

    // Move to the last node in the list
    while (lst->next)
        lst = lst->next;

    ft_printf("\n");
    // Iterate backwards using prev
    while (lst)
    {
        ft_printf("\t\t\t%s", lst->content[0]);
        ft_printf(" , (%t)", lst->type);
        if (lst->subtype == DBL_Q || lst->subtype == SNG_Q)
            ft_printf(", (%t)", lst->subtype);
        if (lst->content[1])
            ft_printf("\n\t\t\t\targs: ");
        n = 1;
        while (lst->content[n])
            ft_printf("%s ", lst->content[n++]);
        // Print parent, left, and right pointers
        // ft_printf("\n\t\t\t\tparent: %s", (lst->parent ? lst->parent->content : "NULL"));
        // ft_printf("\n\t\t\t\tleft: %s", (lst->left ? lst->left->content : "NULL"));
        // ft_printf("\n\t\t\t\tright: %s", (lst->right ? lst->right->content : "NULL"));
        // ft_printf("\n");
        ft_printf("\n");
        lst = lst->prev;
    }
    ft_printf("\n");
    ft_printf("\n");
    return ;
}

