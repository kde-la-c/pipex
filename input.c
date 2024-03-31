/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:41:45 by kde-la-c          #+#    #+#             */
/*   Updated: 2023/08/07 13:41:49 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_args(t_args args, int ishdoc)
{
	if (args.argc < 5 + ishdoc)
		print_error("invalid arguments", 1);
	if (ft_strncmp("here_doc", args.argv[1], 9) && access(args.argv[1], R_OK))
		perror(args.argv[1]);
}
