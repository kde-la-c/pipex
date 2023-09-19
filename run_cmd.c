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

// int	new_child()
// {

// }

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

int	run_cmd1(char *file1, char *cmd1, char **envp)
{
	int		fd1;
	int		fd2;
	t_exec	cmd;
	char	*path;

	cmd.args = ft_split(cmd1, ' ');
	cmd.envp = envp;
	path = get_path(cmd.args[0], envp);
	if (!path)
		perror_exit(cmd.args[0]);
	cmd.path = ft_strjoin(path, cmd.args[0]);
	fd1 = open(file1, O_RDONLY);
	fd2 = open("tmp", O_WRONLY | O_CREAT, 0777);
	if (fd1 == -1 || fd2 == -1)
		perror_exit("open");
	fd1 = dup2(fd1, STDIN_FILENO);
	fd2 = dup2(fd2, STDOUT_FILENO);
	if (fd1 == -1 || fd2 == -1)
		perror_exit("dup2");
	if (execve(cmd.path, cmd.args, cmd.envp) == -1)
		perror_exit("execve");
	return (0);
}
