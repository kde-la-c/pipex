/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:08:00 by kde-la-c          #+#    #+#             */
/*   Updated: 2023/09/27 14:08:04 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_envpath(t_core *core, char *cmd, char **envp)
{
	t_count	c;
	char	*ret;
	char	*tmp;
	char	**paths;

	ft_bzero((void *)&c, sizeof(t_count));
	while (envp[c.i] && ft_strncmp(envp[c.i], "PATH", 4))
		c.i++;
	paths = ft_split(ft_strnstr(envp[c.i], "=", 7) + 1, ':');
	if (!paths)
		perror_exit(core, "env variables", 128);
	while (paths[c.j] && paths[c.j + 1] && access(ret, F_OK))
	{
		if (c.j)
			free(ret);
		c.j++;
		tmp = ft_strjoin(paths[c.j], "/");
		ret = ft_strjoin_f1(tmp, cmd);
	}
	if (!paths[c.j])
		perror_exit(core, paths[c.j], 127);
	return (ft_dfree((void **)paths), ret);
}

static char	*get_path(t_core *core, char *cmd, char **envp)
{
	if (!cmd)
		return (NULL);
	else if (!*envp)
	{
		if (access(cmd, F_OK) == -1)
			perror_exit(core, cmd, 127);
		return (ft_strdup(cmd));
	}
	else
		return (get_envpath(core, cmd, envp));
}

t_exec	fill_cmd(t_core *core, int cmd_id)
{
	t_exec	ret;
	char	*path;

	ret.args = ft_split(core->commands[cmd_id], ' ');
	if (!ret.args)
	{
		ft_dfree((void *)ret.args);
		perror_exit(core, core->commands[cmd_id], 127);
	}
	ret.envp = core->envp;
	if (access(ret.args[0], X_OK))
		path = get_path(core, ret.args[0], core->envp);
	else
		path = ft_strdup(ret.args[0]);
	if (!path)
		ret.path = NULL;
	else
		ret.path = ft_strdup(path);
	free(path);
	return (ret);
}
