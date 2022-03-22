/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:27:15 by scuter            #+#    #+#             */
/*   Updated: 2022/03/23 00:26:18 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_is_numeric(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_cmd(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
	{
		printf("exit\n");
		exit(0);
	}
	else if (i == 2 && str_is_numeric(argv[1]))
	{
		printf("exit\n");
		exit(ft_atoi(argv[1]));
	}
	else if (i > 2 && str_is_numeric(argv[1]))
		printf("exit: too many arguments\n");
	else
	{
		printf("exit: numeric argument required\n");
		exit(255);
	}
}
