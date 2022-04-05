/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:27:15 by scuter            #+#    #+#             */
/*   Updated: 2022/04/05 02:52:20 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_is_numeric(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '-' || str[i] == '+') && str[i + 1])
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// Exit the bash shell or shell script with a status of N.
void	exit_cmd(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	else if (i == 2 && str_is_numeric(argv[1]))
	{
		ft_putendl_fd("exit", 1);
		exit(ft_atoi(argv[1]));
	}
	else if (i > 2 && str_is_numeric(argv[1]))
		ft_putendl_fd("exit: too many arguments", 2);
	else
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
	}
}
