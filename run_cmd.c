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
	while (paths[c.j]
		&& access(ft_strjoin(ft_strjoin(paths[c.j], "/"), cmd), R_OK))
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

void	redir_fd(char *inpath, int infd, int create, int redirected)
{
	int	fd;

	if (inpath && create)
		fd = open(inpath, O_WRONLY | O_CREAT, 0777);
	else if (inpath && !create)
		fd = open(inpath, O_RDONLY);
	else
		fd = infd;
	if (fd == -1)
		perror_exit(inpath);
	if (dup2(fd, redirected) == -1)
		perror_exit("dup2");
}

void	run_cmd2(char *outfile, char *cmd2, char **envp, int *fds)
{
	int		outfd;
	int		pid;
	t_exec	cmd;

	cmd = fill_cmd(cmd2, envp);
	// THIS redir isn't working
	// redir_fd(NULL, STDIN_FILENO, 0, fds[0]);
	if (dup2(STDIN_FILENO, fds[0]))
		perror_exit("dup2");
	printf("stdin :%s\n", get_next_line(STDIN_FILENO));
	pid = fork();
	if (!pid)
	{
		// redir_fd(outfile, -1, 1, STDOUT_FILENO);
		outfd = open(outfile, O_WRONLY | O_CREAT, 0777);
		dup2(outfd, STDOUT_FILENO);
		if (execve(cmd.path, cmd.args, cmd.envp) == -1)
			perror_exit("execve");
	}
	else
	{
		wait(NULL);
	}
	ft_dfree((void **)cmd.args);
}

void	run_cmd1(char *infile, char *cmd1, char **envp, int *fds)
{
	int		pid;
	t_exec	cmd;

	cmd = fill_cmd(cmd1, envp);
	redir_fd(infile, -1, 0, STDIN_FILENO);
	pid = fork();
	if (!pid)
	{
		redir_fd(NULL, fds[1], 0, STDOUT_FILENO);
		if (execve(cmd.path, cmd.args, cmd.envp) == -1)
			perror_exit("execve");
	}
	else
	{
		wait(NULL);
		// char *str;
		// do
		// {
		// 	str = get_next_line(fds[0]);
		// 	printf("-%s", str);
		// } while (str);
	}
	ft_dfree((void **)cmd.args);
}
