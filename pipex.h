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

# define READ	0
# define WRITE	1

typedef struct s_exec
{
	char	*path;
	char	**args;
	char	**envp;
}	t_exec;

typedef struct s_core
{
	char	**commands;
	char	**envp;
	char	*infile;
	char	*outfile;
	int		nbcommands;
	int		**fds;
	int		*pids;
}	t_core;

// input
void	read_args(int argc, char **argv);

// output
int		print_error(char *err, int status);
int		perror_exit(char *err, int status);

// initialize core
int		**init_pipes(int nbpipes);
void	init_core(t_core *core, int argc, char **argv, char **envp);

// interpret commands
t_exec	fill_cmd(char *cmd, char **envp);

// handle file descriptors and pipes
void	close_both(int *fds);
void	redir_fd(char *srcpath, int srcfd, int create, int dest);

// run commands
int		command_runner(t_core *core);

#endif
