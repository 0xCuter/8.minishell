/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:27:15 by scuter            #+#    #+#             */
/*   Updated: 2022/04/08 11:30:13 by vvandenb         ###   ########.fr       */
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
void	exit_cmd(char **argv, t_data *data)
{
	int	i;

	data->exit_status = 0;
	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
		exit_shell(0);
	else if (i == 2 && str_is_numeric(argv[1]))
		exit_shell((char)ft_atoi(argv[1]));
	else if (i > 2 && str_is_numeric(argv[1]))
	{
		data->exit_status = 1;
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	}
	else
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		// system("leaks minishell");
		exit(255);
	}
}
