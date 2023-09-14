/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:39:50 by kde-la-c          #+#    #+#             */
/*   Updated: 2023/09/08 18:39:53 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	new_child()
// {

// }

int	run_cmd1(char *file1, char *cmd1, char **envp)
{
	int		fd1;
	int		fd2;
	t_exec	cmd;
	(void)cmd1;

	cmd.args = ft_split(cmd1, ' ');
	cmd.envp = envp;
	fd1 = open(file1, O_RDONLY);
	if (fd1 == -1)
		perror_exit(file1);
	fd2 = open("ret", O_RDONLY);
	// fd2 = dup(STDIN_FILENO);
	dup2(fd2, STDIN_FILENO);
	if (fd2 == -1)
		perror_exit("dup2");
	printf("fd2: %i\n", fd2);
	// write(fd2, "hola\nque\ntal", 13);
	// close(fdstdin);
	execve("/bin/wc", cmd.args, cmd.envp);
	return (0);
}
