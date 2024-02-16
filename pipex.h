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
int		run_cmd_first(char *infile, char *command, char **envp, int *fds);
int		run_cmd_last(char *outfile, char *command, char **envp, int *fds);
int		run_cmd_middle(char *command, char **envp, int *fds);

// cmd interpreter
t_exec	fill_cmd(char *cmd, char **envp);

#endif
