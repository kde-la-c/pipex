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

void	run_cmd_last(char *outfile, char *command, char **envp, int *fds)
{
	int		pid;
	t_exec	cmd;

	cmd = fill_cmd(command, envp);
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
				perror_exit(command);
		}
		else
		{
			close(fds[0]);
			close(fds[1]);
			waitpid(pid, NULL, 0);
		}
	}
	ft_dfree((void **)cmd.args);
}

// void	run_cmd_middle(char *command, char **envp, int *fds)
// {
// 	int		pid;
// 	t_exec	cmd;

// 	cmd = fill_cmd(command, envp);
// }

void	run_cmd_first(char *infile, char *command, char **envp, int *fds)
{
	int		pid;
	t_exec	cmd;

	cmd = fill_cmd(command, envp);
	if (!cmd.path)
	{
		redir_fd(infile, -1, 0, fds[0]);
		ft_dfree((void **)cmd.args);
		return ;
	}
	pid = fork();
	if (!pid && !close(fds[0]))
	{
		redir_fd(infile, -1, 0, STDIN_FILENO);
		redir_fd(NULL, fds[1], 0, STDOUT_FILENO);
		close(fds[1]);
		if (execve(cmd.path, cmd.args, cmd.envp) == -1)
			perror_exit(command);
	}
	else
		waitpid(pid, NULL, WNOHANG);
	ft_dfree((void **)cmd.args);
}
