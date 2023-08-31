/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:50:40 by kde-la-c          #+#    #+#             */
/*   Updated: 2023/08/06 15:50:43 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	*open_files(char **argv)
{
	int	*ret;

	ret = ft_calloc(5, sizeof(int));
	ret[0] = open(argv[1], O_RDONLY);
	if (ret[0] == -1)
		perror_exit(argv[1]);
	ret[1] = open(argv[4], O_WRONLY | O_CREAT, 0777);
	if (ret[1] == -1)
		perror_exit(argv[4]);
	return (ret);
}

void	close_fds(int *fds)
{
	while (*fds)
		close(*(fds++));
}

int	main(int argc, char **argv)
{
	char	*str;
	int		*fds;
	t_exec	exec;

	read_args(argc, argv);
	fds = open_files(argv);
	str = get_next_line(fds[0]);
	while (str)
	{
		write(fds[1], str, ft_strlen(str));
		str = get_next_line(fds[0]);
	}
	exec.args = ft_split(argv[2], ' ');
	exec.path = ft_strjoin("/bin/", exec.args[0]);
	exec.envp = (char **)NULL;
	if (execve(exec.path, exec.args, exec.envp) == -1)
		perror_exit("execve");
	close_fds(fds);
	return (0);
}
