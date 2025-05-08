/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hndl_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:57:50 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/08 15:23:19 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc_readline(char *limiter, char *doc_name, t_data *data, int expand)
{
	char	*line;
	int		doc_fd;

	doc_fd = open(doc_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (doc_fd == -1)
		return (free(doc_name),
			error_handler("heredoc: failed to create temporary file", 1), 0);
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
			return (close(doc_fd), 0);
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

int	handle_here_doc(t_list *redir, t_data *data)
{
	char	*limiter;
	char	*doc_name;
	int		expand;
	pid_t	pid;
	int		status;

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
	if (!doc_name)
		return (0);
	redir->content[1] = limiter;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, handle_heredoc_sigint);
		if (!here_doc_readline(limiter, doc_name, data, expand))
			silent_exit(data, 1);
		silent_exit(data, 0);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			redir->content[2] = NULL;
			unlink(doc_name);
			free(doc_name);
			return (0);
		}
	}
		if (!add_arg(redir, doc_name))
		return (free(doc_name), 0);
	return (free(doc_name), 1);
}
