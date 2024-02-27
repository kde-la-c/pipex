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

static int	run_cmd_first(t_core *core, int cmd_id)
{
	t_exec	cmd;

	if (!core->pids[cmd_id])
	{
		cmd = fill_cmd(core->commands[cmd_id], core->envp);
		close(core->fds[cmd_id][READ]);
		redir_fd(core->infile, -1, 0, STDIN_FILENO);
		redir_fd(NULL, core->fds[cmd_id][WRITE], 0, STDOUT_FILENO);
		close(core->fds[cmd_id][WRITE]);
		if (execve(cmd.path, cmd.args, cmd.envp) == -1)
			return (ft_dfree((void **)cmd.args), free(cmd.path), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	run_cmd_middle(t_core *core, int cmd_id)
{
	t_exec	cmd;

	if (!core->pids[cmd_id])
	{
		cmd = fill_cmd(core->commands[cmd_id], core->envp);
		close(core->fds[cmd_id - 1][WRITE]);
		close(core->fds[cmd_id][READ]);
		redir_fd(NULL, core->fds[cmd_id - 1][READ], 0, STDIN_FILENO);
		redir_fd(NULL, core->fds[cmd_id][WRITE], 0, STDOUT_FILENO);
		close(core->fds[cmd_id - 1][READ]);
		close(core->fds[cmd_id][WRITE]);
		if (execve(cmd.path, cmd.args, cmd.envp) == -1)
			return (ft_dfree((void **)cmd.args), free(cmd.path), EXIT_FAILURE);
	}
	else
		close_both(core->fds[cmd_id - 1]);
	return (EXIT_SUCCESS);
}

static int	run_cmd_last(t_core *core, int cmd_id)
{
	t_exec	cmd;

	if (!core->pids[cmd_id])
	{
		cmd = fill_cmd(core->commands[cmd_id], core->envp);
		close(core->fds[cmd_id - 1][WRITE]);
		redir_fd(NULL, core->fds[cmd_id - 1][READ], 0, STDIN_FILENO);
		redir_fd(core->outfile, -1, 1, STDOUT_FILENO);
		close(core->fds[cmd_id - 1][READ]);
		if (execve(cmd.path, cmd.args, cmd.envp) == -1)
			return (ft_dfree((void **)cmd.args), free(cmd.path), EXIT_FAILURE);
	}
	else
		close_both(core->fds[cmd_id - 1]);
	return (EXIT_SUCCESS);
}

int	command_runner(t_core *core)
{
	int	i;

	i = 0;
	while (i < core->nbcommands)
	{
		core->pids[i] = fork();
		if (i == 0 && core->pids[i] == 0)
			return (run_cmd_first(core, i));
		else if (i == core->nbcommands - 1 && core->pids[i] == 0)
			return (run_cmd_last(core, i));
		else if (core->pids[i] == 0)
			return (run_cmd_middle(core, i));
		else
			i++;
	}
	return (EXIT_SUCCESS);
}
