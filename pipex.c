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

int	*open_files(char **argv) //useless?
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

void	close_fds(int *fds) //useless?
{
	while (*fds)
		close(*(fds++));
}

int	main(int argc, char **argv, char **envp)
{
	read_args(argc, argv);
	run_cmd1(argv[1], argv[2], envp);
	return (0);
}
