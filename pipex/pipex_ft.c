/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 23:48:55 by sravizza          #+#    #+#             */
/*   Updated: 2025/02/20 11:40:01 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//uses gnl to read input from the user until "limiter" is found, stores it in a temporary .tmp file.
void	gnl_doc(char *limiter)
{
	char	*line;
	int		doc;

	doc = open(".tmp_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (doc == -1)
		error("open tmp fail", NULL, 0);
	ft_printf("> ");
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)) // stop if line == limiter\n
			&& line[ft_strlen(limiter)] == '\n')
			break ;
		write(doc, line, ft_strlen(line));
		write(doc, "\n", 1);
		free(line);
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(doc);
}
// we create one pipe per pair of commands, and one child process per command
// ex: for cmd1 | cmd2 | cmd3 ; we have 3 cmds and 2 pipes
// so we create 2 pipesm and 3 forks (child processes)

void	pipex(t_pipe *data)
{
	int	pid;
	int	i;

	i = 0;
	while (i < data->n_cmd - 1) // n_pipes = n_cmd - 1 
	{
		if (pipe(data->fd + i * 2) == -1) //man pipe
			error("pipe fail", data, 1);
		i++;
	}
	i = 0;
	while (i < data->n_cmd) // n_forks = n_cmd
	{
		pid = fork(); // man fork, forks processes for each command, stores process id in pid
		if (pid == -1)
			error("fork fail", data, 1);
		if (pid == 0)
			child(i, data->fd, data); // exe child processes
		i++;
	}
	close_and_wait_all(data); // close pipes and wait for child porocesses
	return ;
}

void	child(int i, int *fd, t_pipe *data)
{
	if (i == 0)
		ft_open(data->argv[1], data, 1); // if first cmd, read input from infile (or heredoc)
	else
		dup2(fd[(i - 1) * 2], STDIN_FILENO); // man dup2; else reads from previous pipe
	if (i == data->n_cmd - 1) 
		ft_open(data->argv[data->argc - 1], data, 0); // if last, write output in outfile 
	else
		dup2(fd[i * 2 + 1], STDOUT_FILENO); // else, write in previous pipe
	close_all(data); //close unused file descriptors and execute commands;
	exe(data->argv[i + 2 + data->bonus], data);
}

void	exe(char *argv, t_pipe *data)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' '); // splits command and arguments
	if (!cmd || !cmd[0])
	{
		free_all(cmd);
		error("'' :command not found", data, 1);
	}
	//find the executable path
	path = pathfinder(cmd[0], data);
	if (!path)
	{
		ft_putstr_fd(cmd[0], 2);
		free_all(cmd);
		free(path);
		error(" :command not found", data, 1);
	}
	// execute cmd with given args
	if (execve(path, cmd, data->envp) == -1) //man execve
	{
		free_all(cmd);
		free(path);
		error("exe fail", data, 1);
	}
	free(path);
	return ;
}

char	*pathfinder(char *cmd, t_pipe *data)
{
	char	**all_paths;
	char	*path;
	char	*temp;
	int		i;

	if (!data->envp)
		return (NULL);
	//locate PATH in environment
	i = 0;
	while (data->envp[i] && ft_strnstr(data->envp[i], "PATH=", 5) == 0)
		i++;
	//split PATH into individual directories
	all_paths = ft_split(data->envp[i] + 5, ':');
	// Try them all out to find the command
	i = 0;
	while (all_paths[i])
	{
		temp = ft_strjoin(all_paths[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	free_all(all_paths);
	return (NULL);
}
