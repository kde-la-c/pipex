/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:45:21 by kde-la-c          #+#    #+#             */
/*   Updated: 2023/08/07 13:45:23 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_struct(t_core *core)
{
	int	i;

	i = -1;
	if (core)
	{
		if (core->fds)
		{
			while (++i < core->nbcommands)
				free(core->fds[i]);
			free(core->fds);
		}
		if (core->pids)
			free(core->pids);
		if (core->commands)
			free(core->commands);
		free(core);
	}
}

int	print_error(char *err, int status)
{
	write(2, &err[0], ft_strlen(err));
	write(2, "\n", 1);
	exit(status);
}

int	perror_exit(t_core *core, char *err, int status)
{
	free_struct(core);
	perror(err);
	exit(status);
}
