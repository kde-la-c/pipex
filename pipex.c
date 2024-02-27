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
	t_core	*core;

	i = 0;
	read_args(argc, argv);
	core = (t_core *)malloc(sizeof(t_core));
	if (!core)
		perror_exit("structure", EXIT_FAILURE);
	init_core(core, argc, argv, envp);
	j = command_runner(core);
	if (j)
		perror_exit("cmd", j);
	while (i < core->nbcommands && core->pids[i] == 0)
	{
		waitpid(core->pids[i], NULL, 0);
		i++;
	}
	return (EXIT_SUCCESS);
}
