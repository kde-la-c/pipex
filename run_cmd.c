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

void	redir_fd(char *inpath, int infd, int create, int redirected)
{
	int	fd;

	if (inpath && create)
		fd = open(inpath, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (inpath && !create)
		fd = open(inpath, O_RDONLY);
	else
		fd = infd;
	if (fd == -1)
		perror_exit(inpath);
	if (dup2(fd, redirected) == -1)
		perror_exit("dup2");
	close(fd);
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
		if (execve(cmd.path, cmd.args, cmd.envp) == -1)
			perror_exit(cmd2);
	}
	ft_dfree((void **)cmd.args);
}

void	run_cmd1(char *infile, char *cmd1, char **envp, int *fds)
{
	int		pid;
	t_exec	cmd;

	cmd = fill_cmd(cmd1, envp);
	pid = fork();
	if (!pid)
	{
		close(fds[0]);
		redir_fd(infile, -1, 0, STDIN_FILENO);
		redir_fd(NULL, fds[1], 0, STDOUT_FILENO);
		if (execve(cmd.path, cmd.args, cmd.envp) == -1)
			perror_exit(cmd1);
	}
	ft_dfree((void **)cmd.args);
	free(cmd.path);
}
