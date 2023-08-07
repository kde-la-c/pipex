/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:45:21 by kde-la-c          #+#    #+#             */
/*   Updated: 2023/08/07 13:45:23 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	print_error(char *err)
{
	write(2, &err[0], ft_strlen(err));
	write(2, "\n", 1);
	exit(1);
}

int	perror_exit(char *err)
{
	perror(err);
	exit(1);
}
