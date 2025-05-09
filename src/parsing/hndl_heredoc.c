/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hndl_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:57:50 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/09 12:18:05 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc_readline(char *limiter, char *doc_name, t_data *data, int expand)
{
	char	*line;
	int		doc_fd;

	doc_fd = open(doc_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (doc_fd == -1)
		return (ft_free(&doc_name),
			exit_handler(data, "heredoc: failed to create temporary file", 1), 0);
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

void	handle_heredoc_sigint(int signum)
{
    (void)signum;
    write(1, "\n", 1);
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
    exit(130);
}

void	heredoc_signint(int signum)
{
	(void) signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();

	// rl_redisplay();
	g_exit_code = 130;
}

void	signal_heredoc(t_data *data)
{
	struct sigaction	sa;

	signal(SIGQUIT, SIG_IGN);
	sa.sa_handler = heredoc_signint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit_handler(data, "sigaction", 1);
}

int	handle_here_doc(t_list *redir, t_data *data)
{
	char	*limiter;
	char	*doc_name;
	int		expand;
	pid_t	pid;
	int		status;
	// int		i;

	expand = 1;
	limiter = redir->content[1];
	if (limiter[0] == '\'' || limiter[0] == '\"')
	{
		expand = 0;
		limiter = update_quotes(limiter);
		if (!limiter)
			return (error_handler("ast: memory allocation failed", 1), 0);
	}
	doc_name = ft_strjoin_free_two(".heredoc_", ft_itoa(data->here_doc));
	data->here_doc++;
	if (!doc_name)
		return (0);
	redir->content[1] = limiter;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		// signal_heredoc(data);
		if (!here_doc_readline(limiter, doc_name, data, expand))
			silent_exit(data, 1);
		silent_exit(data, 0);
	}
	else if (pid > 0)
	{
		// signal_restore(data);
		// i = 0;
		// while (i++ <= data->here_doc)
		// {
			waitpid(-1, &status, 0);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			{
				unlink(doc_name);
				free_heredocs_sigint(redir);
				// ft_free(&doc_name);
				// redir->content[2] = NULL;
				// rl_redisplay();
				g_exit_code = 130;
				// write(1, "\n", 1);
				// rl_replace_line("", 0);
				// rl_on_new_line();
				signal_restore(data);
				return (0);
			// }
		}
	}
	signal_restore(data);
	if (!add_arg(redir, doc_name))
		return (free(doc_name), 0);
	return (free(doc_name), 1);
}

void free_heredocs(t_list *lst)
{
	t_list *node;

	while (lst)
	{
		// if (lst->type == HEREDOC && lst->content[2])
		// {
		// 	ft_putendl_fd(lst->content[2], 2);
		// 	unlink(lst->content[2]);
		// }
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

void free_heredocs_sigint(t_list *lst)
{
	// t_list *node;

	while (lst->prev)
		lst = lst->prev;
	while (lst)
	{
		if (lst->type == HEREDOC && lst->content[2])
		{
			// ft_putendl_fd(lst->content[2], 2);
			unlink(lst->content[2]);
		}
		// if (lst->read)
		// {
		// 	node = lst->read;
		// 	while (node)
		// 	{
		// 		if (node->type == HEREDOC && node->content[2])
		// 			unlink(node->content[2]);
		// 		node = node->next;
		// 	}
		// }
		lst = lst->next;
	}
}
