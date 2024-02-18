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
	int	i;
	int	fds[2][2];

	i = 4;
	// fds = malloc(sizeof(int) * 2 * (argc - ));
	if (pipe(fds[0]) == -1)
		perror_exit("pipe");
	if (pipe(fds[1]) == -1)
		perror_exit("pipe");
	read_args(argc, argv);
	if (run_cmd_first(argv[1], argv[2], envp, fds[0]))
		perror_exit(argv[2]);
	while (i < argc - 1)
	{
		if (run_cmd_middle(argv[i], envp, fds[i % 2], fds[(i + 1) % 2]))
			perror_exit(argv[i]);
		i++;
	}
	if (run_cmd_last(argv[argc - 1], argv[argc - 2], envp, fds[(i) % 2]))
		perror_exit(argv[3]);
	ft_putstr_fd("hey\n", 2);
	close_both(fds[1]);
	// close_both(fds[0]);
	return (0);
}
