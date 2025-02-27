/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:39:07 by sravizza          #+#    #+#             */
/*   Updated: 2024/11/07 17:56:29 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_fd(int fd, char *stat_str);
static char	*get_output(char *stat_str);
static char	*get_leftover(char *stat_str);
static char	*ft_strjoin_and_free(char *str1, char *str2);

char	*get_next_line(int fd)
{
	char		*out;
	static char	*stat;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stat = read_fd(fd, stat);
	if (!stat)
		return (NULL);
	out = get_output(stat);
	stat = get_leftover(stat);
	return (out);
}

static char	*read_fd(int fd, char *stat)
{
	char	buf[BUFFER_SIZE + 1];
	int		n;

	if (!stat)
		stat = ft_calloc(1, 1);
	n = 1;
	while (n > 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n == -1)
			return (free(stat), NULL);
		buf[n] = 0;
		stat = ft_strjoin_and_free(stat, buf);
		if (ft_strchr(stat, '\n'))
			break ;
	}
	return (stat);
}

static char	*get_output(char *stat)
{
	char	*dest;
	int		n;

	n = 0;
	if (!stat[n])
		return (NULL);
	while (stat[n] && stat[n] != '\n')
		n++;
	dest = ft_calloc(n + 2, sizeof(char));
	if (!dest)
		return (NULL);
	n = 0;
	while (stat[n] && stat[n] != '\n')
	{
		dest[n] = stat[n];
		n++;
	}
	if (stat[n] && stat[n] == '\n')
		dest[n++] = '\n';
	return (dest);
}

static char	*get_leftover(char *stat)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	while (stat[i] && stat[i] != '\n')
		i++;
	if (!stat[i])
		return (free(stat), NULL);
	dest = ft_calloc((ft_strlen(stat) - i + 1), sizeof(*stat));
	if (!dest)
		return (NULL);
	j = 0;
	i++;
	while (stat[i])
		dest[j++] = stat[i++];
	return (free(stat), dest);
}

static char	*ft_strjoin_and_free(char *str1, char *str2)
{
	char	*dest;
	int		i;

	dest = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!dest)
		return (0);
	i = 0;
	while (str1[i])
	{
		dest[i] = str1[i];
		i++;
	}
	i = 0;
	while (str2[i])
	{
		dest[ft_strlen(str1) + i] = str2[i];
		i++;
	}
	dest[ft_strlen(str1) + i] = 0;
	free(str1);
	return (dest);
}
