/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:32:22 by sravizza          #+#    #+#             */
/*   Updated: 2025/03/10 15:54:14 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief is  < << >> > ?
 */
int	is_redir(t_type	type)
{
	if (type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC)
		return (1);
	return (0);
}

int	is_operator(t_type type)
{
	if (is_redir(type) || type == PIPE)
		return (1);
	return (0);
}

int	char_is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	count_split(char *old)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (old[i])
	{
		if (old[i] == '\'')
		{
			count++;
			while (old[i] && old[i] != '\'')
				i++;
			if (!old[i])
				break;
		}
		if (old[i] == '\"')
		{
			count++;
			while (old[i] && old[i] != '\'')
				i++;
			if (!old[i])
				break;
		}
		else
		{
			count++;
			while (old[i] && old[i] != '\'' && old[i] != '\"')
				i++;
			if (!old[i])
				break; 
		}
		i++;
	}
	return (count);
}

int	rework_token(char *old, t_data *data)
{
	char	**temp;
	char	*dest;
	int		i;
	int		len;

	temp = 


}

int	rework_token_main(t_list *lst, t_data *data)
{
	while (lst)
	{
		if (lst->type == WORD)
			lst->content[0] = rework_token(lst->content[0], data);
		if (!lst->content[0])
			return (0);
		lst = lst->next;
	}
	return (1);
}

char	*rework_token(char *old, t_data *data)
{
	int		o;
	int		n;
	int		len;
	char	*new;

	len = ft_strlen(old);
	new = malloc(sizeof(char *) * len + 1);
	if (!new)
		return (error_handler("ast: memory allocation failed", 2), NULL);
	o = 0;
	n = 0;
	while (old[o])
	{
		if (old[o] != '\'' || old[o] != '\"')
			new[n++] = old[o++];
		if (old[o] == '\'')
		{
			o++;
			while (old[o] && old[o] != '\'')
			{
				new[n++] = old[o++];
			}
			o++;
			if (!old[o])
				break ;
		}
		if (old[o] == '\"')
		{
			o++;
			new = dblq_replace_env(data, new);
			if (!new)
				return (NULL);
			o++;
			if (!old[o])
				break ; 
		}
	}
	ft_free(&old);
	new[n] = 0;
	return (new);
}

