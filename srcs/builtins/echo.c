/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:03:34 by scuter            #+#    #+#             */
/*   Updated: 2022/04/08 16:22:23 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Write arguments to the standard output separated by
// a single space character and followed by a newline.
// Option -n:	do not append a newline.
void	echo_cmd(char **argv, t_data *data)
{
	int	n_flag;
	int	i;
	int j;

	data->exit_status = 0;
	n_flag = 0;
	i = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j] == 'n')
			j++;
		if (!argv[i][j])
		{
			n_flag = 1;
			i++;
		}
		else
			break ;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
		if (argv[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!n_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
