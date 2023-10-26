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

void	close_both(int *fds)
{
	if (close(fds[0]))
		perror_exit("read pipe fd");
	if (close(fds[1]))
		perror_exit("write pipe fd");
}

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

void	copy_paste(int *fds, char *outfile)
{
	int		outfd;
	char	*line;

	close(fds[1]);
	outfd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfd == -1)
		perror_exit(outfile);
	line = get_next_line(fds[0]);
	while (line)
	{
		write(outfd, line, ft_strlen(line));
		free(line);
		line = get_next_line(fds[0]);
	}
	free(line);
}

int	run_cmd2(char *outfile, char *cmd2, char **envp, int *fds)
{
	int		pid;
	t_exec	cmd;

	cmd = fill_cmd(cmd2, envp);
	if (!cmd.path)
		copy_paste(fds, outfile);
	else
	{
		pid = fork();
		if (!pid && !close(fds[1]))
		{
			redir_fd(NULL, fds[0], 0, STDIN_FILENO);
			redir_fd(outfile, -1, 1, STDOUT_FILENO);
			close(fds[0]);
			if (execve(cmd.path, cmd.args, cmd.envp) == -1)
				return (ft_dfree((void **)cmd.args), 1);
		}
		else
		{
			close_both(fds);
			waitpid(pid, NULL, 0);
		}
	}
	return (ft_dfree((void **)cmd.args), 0);
}

int	run_cmd1(char *infile, char *cmd1, char **envp, int *fds)
{
	int		pid;
	t_exec	cmd;

	cmd = fill_cmd(cmd1, envp);
	if (!cmd.path)
	{
		redir_fd(infile, -1, 0, fds[0]);
		return (ft_dfree((void **)cmd.args), 1);
	}
	pid = fork();
	if (!pid && !close(fds[0]))
	{
		redir_fd(infile, -1, 0, STDIN_FILENO);
		redir_fd(NULL, fds[1], 0, STDOUT_FILENO);
		close(fds[1]);
		if (execve(cmd.path, cmd.args, cmd.envp) == -1)
			return (ft_dfree((void **)cmd.args), 1);
	}
	else
		waitpid(pid, NULL, WNOHANG);
	return (ft_dfree((void **)cmd.args), 0);
}
