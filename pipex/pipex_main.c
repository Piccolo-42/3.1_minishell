/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:25:19 by sravizza          #+#    #+#             */
/*   Updated: 2025/02/19 17:33:33 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/**
 * in pipex, the scope is to replicate shell commands, i.e:
 * 
 * >: 		./pipex file1 cmd1 cmd2 file2			behaves like:
 * >:		< file1 cmd1 | cmd2 > file2
 * 
 * 
 * this project also includes 2 bonuses:
 * 
 * - here_doc (<<), allows for user input in the terminal, instead of a infile
 * - allow for multiple pipes, i.e:
 * 
 * >:			./pipex file1 cmd1 cmd2 cmd3 ... cmd(n) file2	behaves like:
 * >:			< file1 cmd1 | cmd2 | cmd3 | ... | cmd(n) > file2
 * 
 * Crash course on redirections and pipes at the bottom of main() 
 * these are key notions or functions you need to understand for the functioning of pipex
 * 		man: 
 * 			- envp / environment variables
 * 			- fork() / (child processes)
 * 			- pipe()
 * 			- dup2()
 * 			- execv()
 * 			- waitpid()
 * 			(open(), close(), you probs know these already)
 * 
 */
int	main(int argc, char **argv, char **envp)
{
	t_pipe	data;
	int		*fd;

	if (argc < 5) // only aplies to pipex as the format is always as shown above 
		return (ft_printf("ding dong your format is wrong"), 0);
	data.argc = argc;
	data.argv = argv;
	data.envp = envp; // man envp
	data.n_cmd = argc - 3; // number of commands to execute (total - (2 files) - program name)
	data.bonus = 0; //bool
	if (ft_strncmp(argv[1], "here_doc", 8) == 0) //bonus, handle here_doc
	{
		gnl_doc(argv[2]); // read user input until limiter (argv[2])
		data.n_cmd = argc - 4; // -1 more for the limter
		data.bonus = 1; // here_doc mode
	}
	fd = malloc(sizeof(int) * 2 * (data.n_cmd - 1)); 	// Allocate space for pipe file descriptors, see pipex() for more info
	if (!fd)
		error("fd malloc fail", NULL, 0);
	data.fd = fd;
	pipex(&data); // exe pipeline
	return (0);
}

/**
 * bash syntax crash course:
 * 
 * 
 * Pipes:
 * 
 * " | " is called a pipe, it redirects output from the left side and gives it as input to the right side
 * 		ex: cmd1 | cmd2 :
 * 				- cmd1 takes input from stdin, but instead of writing into stdout, it writes into the pipe
 * 				- cmd2 takes input from the pipe, and writes onto stdout
 * 
 * 
 * 
 * Redirectrions: 
 * 
 * " <, <<, >, >> " allow to change input or outup from stdin/out to a file. 
 * with <, >, >>, (not <<), the following word is always the name of the file (<infile, >outfile, >>outfile)
 * with << the following word is always the limiter (<<limiter)
 * 
 * - <infile is a redir_in. meaning it's corresponding command will read input from file infile.
 * 
 * - >outfile is redir_out. corresponding cmd will write output to file outfile. 
 * 				note: it will create the file if it doesn't exist, and overite it if it does
 * 
 * - >>outfile is append. same as outfile, but will append the result at the end of the file instead of overwriting it.
 * 
 * - <<limiter is a here_doc. this means once the command line has been sent out (ex: << END wc -l), before launching the command, 
 * 		the porompt is given back for the user to type the document in the terminal, until "limiter" is written (in our case, END)
 * 		try it out in pipex! the syntax for it is (here_doc limiter cmd1 cmd2 outfile)
 * 
 * 
 * 
 * 
 * test commands to familiarise yourself with syntax, pipes and redirs!
 * easiest way (i found) was to create a test.txt file with text in it (anything)
 * 
 * >: 		<test.txt grep "hello world" | grep hello | wc -l > out.txt
 * 
 * this line will:
 * 		- look for any line containing "hello world" in infile
 * 		- from the output of the previous, look of any lines containing hello
 * 		- from the output of the previous, count the lines and write the result in out.txt
 */