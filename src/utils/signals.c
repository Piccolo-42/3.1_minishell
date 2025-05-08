/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:48:18 by sravizza          #+#    #+#             */
/*   Updated: 2025/05/08 15:12:30 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Child process
// if (pid == 0)
// {
//     signal(SIGINT, SIG_DFL);   // Reset SIGINT to default behavior
// }

// int status;
// int sig;
// pid_t pid = waitpid(child_pid, &status, 0);

// if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
// {
// 	write(1, "\n", 1);
// }

// ctrlc in HEREDOC
// ctrl\ in cat non interactive

void	handle_signint(int signum)
{
	(void) signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_code = 130;
}

void	signal_init(t_data *data)
{
	struct sigaction	sa;

	signal(SIGQUIT, SIG_IGN);

	sa.sa_handler = handle_signint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit_handler(data, "sigaction", 1);
}

void	restore_signint(int signum)
{
	(void) signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	// rl_redisplay();
	g_exit_code = 130;
}

void	signal_restore(t_data *data)
{
	struct sigaction	sa;

	signal(SIGQUIT, SIG_IGN);
	sa.sa_handler = restore_signint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit_handler(data, "sigaction", 1);
}

void	handle_sigquit_child(int signum)
{
	(void) signum;
	kill(getpid(), SIGQUIT);
	ft_putstr_fd("Quit (core dumped)", 1);
	// write(1, "\n", 1);
	// rl_replace_line("", 0);
	// rl_on_new_line();
}

void	child_signal(t_data *data)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigquit_child;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		{
			// ft_putstr_fd("Quit (core dumped)", 1);
			exit_handler(data, "sigaction", 1);
		}
}

// void	child_signal(t_data *data)
// {
// 	signal(SIGQUIT, SIG_DFL);
// 	signal(SIGINT, SIG_DFL);
// }
