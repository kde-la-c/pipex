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

void	close_both(int *fds)
{
	if (close(fds[0]))
		perror_exit("close read pipe");
	if (close(fds[1]))
		perror_exit("close write pipe");
}

void	redir_fd(char *srcpath, int srcfd, int create, int dest)
{
	if (srcpath && create)
		srcfd = open(srcpath, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (srcpath && !create)
		srcfd = open(srcpath, O_RDONLY);
	if (srcfd == -1)
		perror_exit(srcpath);
	if (dup2(srcfd, dest) == -1)
		perror_exit("dup");
	close(srcfd);
}

void	copy_paste(int *fds, char *outfile)
{
	int		outfd;
	char	*line;

	close(fds[1]);
	outfd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfd == -1)
		perror_exit(outfile);
	line = get_next_line(fds[0]);
	while (line)
	{
		write(outfd, line, ft_strlen(line));
		free(line);
		line = get_next_line(fds[0]);
	}
	free(line);
}
