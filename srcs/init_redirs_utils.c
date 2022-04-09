/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirs_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:52:16 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/09 15:59:51 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_open(int **fd, char *arg, char *r)
{
	free_null((void *)fd);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror(NULL);
	*r = 1;
}

void	close_free(int *fd)
{
	close(*fd);
	free(fd);
}

char	free_ret_1(char *arg)
{
	free(arg);
	return (1);
}
