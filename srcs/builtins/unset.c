/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:36:21 by scuter            #+#    #+#             */
/*   Updated: 2022/04/07 17:45:25 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_unset_arg(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (1);
	i++;
	while (arg[i])
	{
		if ((!ft_isalnum(arg[i]) && arg[i] != '_') || arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	unset_cmd(char **argv, t_data *data)
{
	char	*envar;
	int		i;

	data->exit_status = 0;
	i = 1;
	while (argv[i])
	{
		if (check_unset_arg(argv[i]))
		{
			data->exit_status = 1;
			ft_putstr_fd("minishell: unset: '", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		}
		else
		{
			envar = find_envar(data, argv[i]);
			if (envar)
				data->envs = remove_line(envar, data->envs);
		}
		i++;
	}
}
