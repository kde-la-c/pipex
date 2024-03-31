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

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		j;
	int		ishdoc;
	t_core	*core;
	t_args	args;

	i = -1;
	args.argc = argc;
	args.argv = argv;
	args.envp = envp;
	ishdoc = (argc > 1 && !ft_strncmp("here_doc", argv[1], 9));
	read_args(args, ishdoc);
	core = (t_core *)malloc(sizeof(t_core));
	if (!core)
		perror_exit("structure", EXIT_FAILURE);
	init_core(core, args, ishdoc);
	j = command_runner(core);
	if (j)
		perror_exit("cmd", j);
	while (++i < core->nbcommands && core->pids[i] == 0)
		waitpid(core->pids[i], NULL, 0);
	return (EXIT_SUCCESS);
}
