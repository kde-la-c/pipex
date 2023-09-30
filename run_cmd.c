/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:39:50 by kde-la-c          #+#    #+#             */
/*   Updated: 2023/09/08 18:39:53 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*	dup2(old_fd, new_fd);
	old_fd("file1") new_fd("file2")
	old_fd("file1") new_fd(VOID)
->	old_fd("file1") new_fd("file1")

	old_fd("file1") new_fd("file1")
->	old_fd("file1") new_fd("file1")
*/

void	redir_fd(char *srcpath, int srcfd, int create, int dest)
{
	if (srcpath && create)
		srcfd = open(srcpath, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (srcpath && !create)
		srcfd = open(srcpath, O_RDONLY);
	if (srcfd == -1)
		perror_exit(srcpath);
	if (dup2(srcfd, dest) == -1)
		perror_exit("dup");
	close(srcfd);
}

void	run_cmd2(char *outfile, char *cmd2, char **envp, int *fds)
{
	int		pid;
	t_exec	cmd;

	cmd = fill_cmd(cmd2, envp);
	pid = fork();
	if (!pid)
	{
		close(fds[1]);
		redir_fd(NULL, fds[0], 0, STDIN_FILENO);
		redir_fd(outfile, -1, 1, STDOUT_FILENO);
		close(fds[0]);
		if (execve(cmd.path, cmd.args, cmd.envp) == -1)
			perror_exit(cmd2);
	}
	else
	{
		// ft_fdprintf(2, "pid %s %i\n", cmd.path, pid);
		close(fds[0]);
		close(fds[1]);
		waitpid(pid, NULL, 0);
	}
	ft_dfree((void **)cmd.args);
}

void	run_cmd1(char *infile, char *cmd1, char **envp, int *fds)
{
	int		pid;
	t_exec	cmd;
	int		*wstatus = NULL;

	cmd = fill_cmd(cmd1, envp);
	pid = fork();
	if (!pid)
	{
		close(fds[0]);
		redir_fd(infile, -1, 0, STDIN_FILENO);
		redir_fd(NULL, fds[1], 0, STDOUT_FILENO);
		close(fds[1]);
		if (execve(cmd.path, cmd.args, cmd.envp) == -1)
			perror_exit(cmd1);
	}
	else
	{
		// ft_fdprintf(2, "pid %s %i\n", cmd.path, pid);
		waitpid(pid, wstatus, WNOHANG);
	}
	ft_dfree((void **)cmd.args);
	free(cmd.path);
}
