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
	int	fds[2];

	if (pipe(fds) == -1)
		perror_exit("pipe");
	read_args(argc, argv);
	run_cmd_first(argv[1], argv[2], envp, fds);
	run_cmd_last(argv[argc - 1], argv[argc - 2], envp, fds);
	close(fds[0]);
	close(fds[1]);
	return (0);
}
