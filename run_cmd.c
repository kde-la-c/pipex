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
	char	*var;
	char	*ret;
	char	**paths;

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
	ft_dfree((void **)paths);
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
	free(path);
	return (ret);
}

void	open_fds(char *inpath)
{
	int	fd;

	fd = open(inpath, O_RDONLY);
	if (fd == -1)
		perror_exit("open");
	if (dup2(fd, STDIN_FILENO) == -1)
		perror_exit("dup2");
}

int	run_cmd1(char *file1, char *cmd1, char **envp)
{
	int		pid;
	int		*fds;
	t_exec	cmd;

	fds = (int *)calloc(2, sizeof(int));
	cmd = fill_cmd(cmd1, envp);
	open_fds(file1);
	if (pipe(fds) == -1)
		perror_exit("pipe");
	pid = fork();
	if (!pid) //child process
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		if (execve(cmd.path, cmd.args, cmd.envp) == -1)
			perror_exit("execve");
	}
	else //parent process
	{
		close(fds[1]);
		wait(NULL);
		printf("parent :%s", get_next_line(fds[0]));
	}
	free(fds);
	ft_dfree((void **)cmd.args);
	return (0);
}
