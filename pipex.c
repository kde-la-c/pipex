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

int	**init_pipes(int nbpipes)
{
	int	i;
	int	**fds;

	i = 0;
	fds = (int **)malloc(sizeof(int *) * nbpipes);
	if (!fds)
		perror_exit("file descriptor");
	while (i < nbpipes)
	{
		fds[i] = (int *)malloc(sizeof(int) * 2);
		if (!fds)
		{
			ft_dfree((void **)fds);
			perror_exit("file descriptors");
		}
		if (pipe(fds[i]) == -1)
		{
			ft_dfree((void **)fds);
			perror_exit("pipe creation");
		}
		i++;
	}
	return (fds);
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	**fds;

	i = 3;
	fds = init_pipes(argc - 4);
	read_args(argc, argv);
	if (run_cmd_first(argv[1], argv[2], envp, fds[0]))
		perror_exit(argv[2]);
	while (++i < argc - 5)
	{
		if (run_cmd_middle(argv[i], envp, fds[i], fds[i + 1]))
			perror_exit(argv[i]);
	}
	if (run_cmd_last(argv[argc - 1], argv[argc - 2], envp, fds[i]))
		perror_exit(argv[3]);
	return (0);
}
