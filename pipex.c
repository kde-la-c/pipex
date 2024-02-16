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
	if (run_cmd_first(argv[1], argv[2], envp, fds))
		perror_exit(argv[2]);
	if (run_cmd_last(argv[argc - 1], argv[argc - 2], envp, fds))
		perror_exit(argv[3]);
	close(fds[0]);
	close(fds[1]);
	return (0);
}
