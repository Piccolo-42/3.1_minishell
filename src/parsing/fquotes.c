/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fquotes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:12:17 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/10 12:51:48 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fquotes(t_list *lst, t_data *data)
{
	int	i;

	while (lst)
	{
		if (lst->type == CMD || (is_redir(lst->type) && lst->type != HEREDOC))
		{
			i = 0;
			while (lst->content[i])
			{
				if (is_redir(lst->type))
					i++;
				lst->content[i] = rework_token(lst->content[i], data);
				if (!lst->content[i])
					return (0);
				i++;
			}
		}
		lst = lst->next;
	}
	return (1);
}

char	*rework_token(char *old, t_data *data)
{
	char	**temp;
	char	*dest;

	temp = token_split(old);
	if (!temp)
		return (NULL);
	if (!modify_substrings(temp, data))
		return (NULL);
	dest = ft_union_simple(temp);
	if (!dest)
		return (NULL);
	ft_free_double(temp);
	ft_free(&old);
	return (dest);
}

char	**token_split(char *old)
{
	char	**temp;
	int		size;
	int		t;
	int		o;

	size = count_split(old);
	temp = malloc(sizeof(char *) * (size + 1));
	if (!temp)
		return (error_handler("memory allocation failed", 1), NULL);
	o = 0;
	t = 0;
	while (t < size)
	{
		temp[t] = get_substring(old, &o);
		if (!temp[t])
			return (ft_free_double(temp),
				error_handler("memory allocation failed", 1), NULL);
		t++;
	}
	temp[t] = NULL;
	return (temp);
}

char	*get_substring(char *old, int *o)
{
	int		start;
	char	quote;

	while (old[*o])
	{
		if (old[*o] == '\'' || old[*o] == '\"')
		{
			quote = old[*o];
			start = *o;
			(*o)++;
			while (old[*o] != quote)
				(*o)++;
			(*o)++;
			return (ft_substr(old, start, (*o) - start));
		}
		else
		{
			start = *o;
			while (old[*o] && old[*o] != '\'' && old[*o] != '\"')
				(*o)++;
			return (ft_substr(old, start, (*o) - start));
		}
	}
	return (NULL);
}

int	modify_substrings(char **temp, t_data *data)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (temp[i][0] == '\'')
			temp[i] = update_quotes(temp[i]);
		else if (temp[i][0] == '\"')
			temp[i] = dblq_replace_env(data,
					update_quotes(temp[i]));
		else
			temp[i] = dblq_replace_env(data, temp[i]);
		if (!temp[i])
			return (0);
		i++;
	}
	return (1);
}
