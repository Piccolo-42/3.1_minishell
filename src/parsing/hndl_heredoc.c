/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hndl_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:57:50 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/10 11:05:14 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main_mock(void)
// {
// 	char *dest;
// 	int pid;

// 	dest = malloc(sizeof(char) * 3);
// 	if (!dest)
// 		return (1);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (!chil_fucntion())
// 			return(silent_exit(dest, 1));
// 		return (silent_exit(dest, 0));
// 	}
// 	else if (pid > 0)
// 		waitpid(-1, NULL, 0);
// 	printf("%s\n", dest);
// 	free(dest);
// 	return (0);
// }

int	here_doc_readline(char *limiter, char *doc_name, t_data *data, int expand)
{
	char	*line;
	int		doc_fd;

	doc_fd = open(doc_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (doc_fd == -1)
		return (ft_free(&doc_name),
			exit_handler(data, "heredoc: failed to create temp file", 1), 0);
	while (1)
	{
		line = readline("> ");
		if ((!line) || (line && !ft_strncmp(line, limiter, ft_strlen(limiter))
				&& ft_strlen(line) == ft_strlen(limiter)))
		{
			ft_free(&line);
			break ;
		}
		if (expand)
			line = dblq_replace_env(data, line);
		if (!line)
			return (close(doc_fd), silent_exit(data, 1), 0);
		write(doc_fd, line, ft_strlen(line));
		write(doc_fd, "\n", 1);
		ft_free(&line);
	}
	return (close(doc_fd), 1);
}

int	heredoc_fork(char *doc_name, char *limiter, t_data *data, t_list *redir)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (!here_doc_readline(limiter, doc_name, data, data->expand_here_doc))
			silent_exit(data, 1);
		silent_exit(data, 0);
	}
	else if (pid > 0)
	{
		signal_restore(data);
		waitpid(-1, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			unlink(doc_name);
			free_heredocs_sigint(redir);
			ft_free(&doc_name);
			g_exit_code = 130;
			return (0);
		}
	}
	return (1);
}

int	handle_here_doc(t_list *redir, t_data *data)
{
	char	*limiter;
	char	*doc_name;

	data->expand_here_doc = 1;
	limiter = redir->content[1];
	if (limiter[0] == '\'' || limiter[0] == '\"')
	{
		data->expand_here_doc = 0;
		limiter = update_quotes(limiter);
		if (!limiter)
			return (error_handler("ast: memory allocation failed", 1), 0);
	}
	doc_name = ft_strjoin_free_two(".heredoc_", ft_itoa(data->here_doc));
	data->here_doc++;
	if (!doc_name)
		return (0);
	redir->content[1] = limiter;
	if (!heredoc_fork(doc_name, limiter, data, redir))
		return (0);
	if (!add_arg(redir, doc_name))
		return (ft_free(&doc_name), 0);
	return (ft_free(&doc_name), 1);
}

void	free_heredocs(t_list *lst)
{
	t_list	*node;

	while (lst)
	{
		if (lst->read)
		{
			node = lst->read;
			while (node)
			{
				if (node->type == HEREDOC && node->content[2])
					unlink(node->content[2]);
				node = node->next;
			}
		}
		lst = lst->next;
	}
}

void	free_heredocs_sigint(t_list *lst)
{
	while (lst->prev)
		lst = lst->prev;
	while (lst)
	{
		if (lst->type == HEREDOC && lst->content[2])
			unlink(lst->content[2]);
		lst = lst->next;
	}
}
