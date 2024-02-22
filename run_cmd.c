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

int	run_cmd_first(char *infile, char *command, char **envp, int *fds)
{
	int		pid;
	t_exec	cmd;

	cmd = fill_cmd(command, envp);
	if (!cmd.path)
	{
		redir_fd(infile, -1, 0, fds[0]);
		return (ft_dfree((void **)cmd.args), 1);
	}
	pid = fork();
	if (!pid)
	{
		close(fds[0]);
		redir_fd(infile, -1, 0, STDIN_FILENO);
		redir_fd(NULL, fds[1], 0, STDOUT_FILENO);
		close(fds[1]);
		if (execve(cmd.path, cmd.args, cmd.envp) == -1)
			return (ft_dfree((void **)cmd.args), 1);
	}
	else
	{
		waitpid(pid, NULL, WNOHANG);
	}
	return (ft_dfree((void **)cmd.args), 0);
}

int	run_cmd_middle(char *command, char **envp, int *fdsin, int *fdsout)
{
	int		pid;
	t_exec	cmd;

	cmd = fill_cmd(command, envp);
	if (!cmd.path)
		return (1);
	pid = fork();
	if (!pid)
	{
		close(fdsin[1]);
		close(fdsout[0]);
		redir_fd(NULL, fdsin[0], 0, STDIN_FILENO);
		redir_fd(NULL, fdsout[1], 0, STDOUT_FILENO);
		close(fdsin[0]);
		close(fdsout[1]);
		if (execve(cmd.path, cmd.args, cmd.envp) == -1)
			return (ft_dfree((void **)cmd.args), 1);
	}
	else
	{
		waitpid(pid, NULL, WNOHANG);
	}
	return (ft_dfree((void **)cmd.args), 0);
}

int	run_cmd_last(char *outfile, char *command, char **envp, int *fds)
{
	int		pid;
	t_exec	cmd;

	cmd = fill_cmd(command, envp);
	if (!cmd.path)
		copy_paste(fds, outfile);
	else
	{
		pid = fork();
		if (!pid)
		{
			close(fds[1]);
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
