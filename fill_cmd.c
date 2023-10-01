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

char	*get_envpath(char *cmd, char **envp)
{
	t_count	c;
	char	*ret;
	char	*tmp;
	char	**paths;

	ft_bzero((void *)&c, sizeof(t_count));
	while (envp[c.i] && ft_strncmp(envp[c.i], "PATH", 4))
		c.i++;
	paths = ft_split(ft_strnstr(envp[c.i], "=", 7) + 1, ':');
	tmp = ft_strjoin(paths[c.j], "/");
	ret = ft_strjoin_f1(tmp, cmd);
	while (paths[c.j] && paths[c.j + 1] && access(ret, F_OK))
	{
		free(ret);
		c.j++;
		tmp = ft_strjoin(paths[c.j], "/");
		ret = ft_strjoin_f1(tmp, cmd);
	}
	if (!paths[c.j])
		perror_exit(paths[c.j]);
	ft_dfree((void **)paths);
	return (ret);
}

char	*get_path(char *cmd, char **envp)
{
	if (!cmd)
		return (NULL);
	else if (!*envp)
	{
		if (access(cmd, F_OK) == -1)
			perror_exit(cmd);
		return (cmd);
	}
	else
		return (get_envpath(cmd, envp));
}

t_exec	fill_cmd(char *cmd, char **envp)
{
	t_exec	ret;
	char	*path;

	ret.args = ft_split(cmd, ' ');
	ret.envp = envp;
	path = get_path(ret.args[0], envp);
	if (!path)
		ret.path = NULL;
	else
		ret.path = path;
	return (ret);
}
