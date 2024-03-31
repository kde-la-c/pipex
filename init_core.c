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

void	init_core(t_core *core, t_args args, int ishdoc)
{
	int	i;

	i = -1;
	core->nbcommands = (args.argc - 3) - ishdoc;
	if (!ishdoc && !access(args.argv[1], R_OK))
		core->infile = args.argv[1];
	else
		core->infile = NULL;
	if (ishdoc)
		core->delimiter = args.argv[2];
	else
		core->delimiter = NULL;
	core->outfile = args.argv[args.argc - 1];
	core->fds = init_pipes(core->nbcommands - 1);
	core->envp = args.envp;
	core->pids = (int *)ft_calloc(core->nbcommands, sizeof(int));
	if (!core->pids)
		perror_exit("pids", EXIT_FAILURE);
	core->commands = (char **)ft_calloc((core->nbcommands) + 1, sizeof(char *));
	if (!core->commands)
		perror_exit("commands", EXIT_FAILURE);
	while (++i < core->nbcommands)
		core->commands[i] = args.argv[i + 2 + ishdoc];
	core->commands[i] = NULL;
}
