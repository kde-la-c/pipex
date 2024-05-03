/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 23:02:34 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/02/22 23:02:51 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	close_both(int *fds)
{
	if (close(fds[0]))
	{
		print_error("close read pipe", EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (close(fds[1]))
	{
		print_error("close write pipe", EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	redir_fd(char *srcpath, int srcfd, int create, int dest)
{
	if (srcpath && create)
		srcfd = open(srcpath, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (srcpath && !create)
		srcfd = open(srcpath, O_RDONLY);
	if (srcfd == -1)
		return (EXIT_SUCCESS);
	if (dup2(srcfd, dest) == -1)
		return (EXIT_FAILURE);
	close(srcfd);
	return (EXIT_SUCCESS);
}
