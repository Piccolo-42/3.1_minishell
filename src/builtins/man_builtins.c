/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   man_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:02:11 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/26 14:28:22 by emurillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 1. "pwd"
	Simply calls getcwd() to retrieve and print the current working directory.
	No arguments or options to handle.
2. "env"
	Just loops through envp and prints the variables.
	No options or arguments to process.
3. "echo" (with -n option only)
	Basic string printing with a check for -n to suppress the newline.
	Requires simple argument parsing.
4. "exit"
	Calls exit() with the given status code (if any).
	Requires checking if the argument is a valid number and handling edge cases.
5. "cd"
	Calls chdir(), but requires argument handling.
	Needs to support cd (to $HOME) and cd path.
	Error handling (e.g., invalid directory) is necessary.
6. "unset" & 7. "export"
	These modify the environment variable list, requiring a custom storage system.
	unset needs to remove variables properly.
	export requires checking variable validity and updating existing ones.

// Grouping
- "pwd" & "env" → Both just retrieve and print values.
- "echo" & "exit" → Both involve simple argument handling.
- "cd" alone → Needs careful path handling.
- "unset" & "export" → Both modify envp, so they should be tackled together.


//allowed functions
readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,

printf, malloc, free,

write, read, access, open, close, unlink,

execve, fork, pipe, dup, dup2, wait, waitpid, wait3, wait4,

exit, strerror, perror, getenv, getcwd,

signal, sigaction, sigemptyset, sigaddset, kill,

chdir, opendir, readdir, closedir, stat, lstat, fstat,


ttyname, ttyslot, ioctl,  isatty,
tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs
