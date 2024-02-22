/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:50:55 by kde-la-c          #+#    #+#             */
/*   Updated: 2023/08/06 15:50:59 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_exec
{
	char	*path;
	char	**args;
	char	**envp;
}	t_exec;

// input
void	read_args(int argc, char **argv);

// output
int		print_error(char *err);
int		perror_exit(char *err);

// interpret commands
t_exec	fill_cmd(char *cmd, char **envp);

// handle file descriptors and pipes
void	close_both(int *fds);
void	redir_fd(char *srcpath, int srcfd, int create, int dest);
void	copy_paste(int *fds, char *outfile);

// run commands
int		run_cmd_first(char *infile, char *command, char **envp, int *fds);
int		run_cmd_last(char *outfile, char *command, char **envp, int *fds);
int		run_cmd_middle(char *command, char **envp, int *fdsin, int *fdsout);

#endif
