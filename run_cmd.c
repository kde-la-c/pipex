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
	{
		free(ret);
		perror_exit("hey");
	}
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
	ret.path = path;
	return (ret);
}

int	redir_fd(char *inpath, int infd, int create, int redirected)
{
	int	tmp;
	int	fd;

	if (inpath && create)
		fd = open(inpath, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (inpath && !create)
		fd = open(inpath, O_RDONLY);
	else
		fd = infd;
	if (fd == -1)
	{
		perror_exit(inpath);
	}
	tmp = dup2(fd, redirected);
	close(fd);
	if (tmp == -1)
	{
		perror_exit("dup2");
	}
	return (fd);
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
		// ft_fdprintf(2, "%i->%s\n", STDIN_FILENO, get_next_line(STDIN_FILENO));
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
		// ft_fdprintf(2, "%i->%s\n", STDIN_FILENO, get_next_line(STDIN_FILENO));
		if (execve(cmd.path, cmd.args, cmd.envp) == -1)
			perror_exit(cmd1);
	}
	ft_dfree((void **)cmd.args);
	free(cmd.path);
}
