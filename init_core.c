/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:02:38 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/02/27 19:02:53 by kde-la-c         ###   ########.fr       */
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
		perror_exit("file descriptor", EXIT_FAILURE);
	while (i < nbpipes)
	{
		fds[i] = (int *)malloc(sizeof(int) * 2);
		if (!fds[i])
		{
			ft_dfree((void **)fds);
			perror_exit("file descriptors", EXIT_FAILURE);
		}
		if (pipe(fds[i]) == -1)
		{
			ft_dfree((void **)fds);
			perror_exit("pipe creation", EXIT_FAILURE);
		}
		i++;
	}
	return (fds);
}

void	init_core(t_core *core, int argc, char **argv, char **envp)
{
	int	i;

	i = -1;
	core->nbcommands = argc - 3;
	if (!access(argv[1], R_OK))
		core->infile = argv[1];
	else
		core->infile = NULL;
	core->outfile = argv[argc - 1];
	core->fds = init_pipes(core->nbcommands - 1);
	core->envp = envp;
	core->pids = (int *)malloc(sizeof(int) * core->nbcommands);
	if (!core->pids)
		perror_exit("pids", EXIT_FAILURE);
	core->commands = (char **)malloc(sizeof(char *) * (argc - 3) + 1);
	if (!core->commands)
		perror_exit("commands", EXIT_FAILURE);
	while (++i < argc - 3)
		core->commands[i] = argv[i + 2];
}
