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

void	read_args(int argc, char **argv)
{
	if (argc < 5)
		print_error("invalid arguments", 1);
	if (access(argv[1], R_OK))
		perror(argv[1]);
}
