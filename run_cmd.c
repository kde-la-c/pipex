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

char	*get_path(char *cmd, char **envp)
{
	t_count	c;
	char	**paths;
	char	*var;
	char	*ret;

	ft_bzero((void *)&c, sizeof(t_count));
	while (envp[c.i] && ft_strncmp(envp[c.i], "PATH", 4))
		c.i++;
	var = ft_strnstr(envp[c.i], "=", 7) + 1;
	paths = ft_split(var, ':');
	while (paths[c.j] && access(ft_strjoin(ft_strjoin(paths[c.j], "/"), cmd), R_OK))
		c.j++;
	if (!paths[c.j])
		return (NULL);
	ret = ft_strjoin(paths[c.j], "/");
	return (ret);
}

t_exec	fill_cmd(char *cmd, char **envp)
{
	t_exec	ret;
	char	*path;

	ret.args = ft_split(cmd, ' ');
	ret.envp = envp;
	path = get_path(ret.args[0], envp);
	if (!path)
		perror_exit(ret.args[0]);
	ret.path = ft_strjoin(path, ret.args[0]);
	return (ret);
}

void	open_fds(int *infd, int *outfd, char *inpath, char *outpath)
{
	*infd = open(inpath, O_RDONLY);
	//was gonna ensure tmp didn't exist before creating and using it
	//but deleting tmp if it was already existing creates a risk of loosing data
	*outfd = open(outpath, O_WRONLY | O_CREAT, 0777);
	if (*infd == -1 || *outfd == -1)
		perror_exit("open");
	*infd = dup2(*infd, STDIN_FILENO);
	*outfd = dup2(*outfd, STDOUT_FILENO);
	if (*infd == -1 || *outfd == -1)
		perror_exit("dup2");
}

int	run_cmd1(char *file1, char *cmd1, char **envp)
{
	int		fd1;
	int		fd2;
	t_exec	cmd;

	cmd = fill_cmd(cmd1, envp);
	open_fds(&fd1, &fd2, file1, "tmp");
	if (execve(cmd.path, cmd.args, cmd.envp) == -1)
		perror_exit("execve");
	return (0);
}
