/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:36:21 by scuter            #+#    #+#             */
/*   Updated: 2022/03/30 01:53:19 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	get_index(char *argv, t_data *data)
// {
// 	char	**key;
// 	int		i;

// 	if (!data->envs)
// 		return (-1);
// 	key = NULL;
// 	i = 0;
// 	while (data->envs[i])
// 	{
// 		key = ft_split(data->envs[i], '=');
// 		if (!key)
// 			error("MALLOC");
// 		if (!ft_strcmp(argv, key[0]))
// 		{
// 			free_tab(key);
// 			return (i);
// 		}
// 		free_tab(key);
// 		i++;
// 	}
// 	return (-1);
// }

static int	check_unset_arg(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return(1);
	i++;
	while (arg[i])
	{
		if ((!ft_isalnum(arg[i]) && arg[i] != '_') || arg[i] == '=')
			return(1);
		i++;
	}
	return(0);
}

void	unset_cmd(char **argv, t_data *data)
{
	char	*envar;
	int		i;

	if (!argv[1])
	{
		ft_putstr_fd("unset: not enough arguments", 2);
		return ;
	}
	i = 1;
	while (argv[i])
	{
		if (check_unset_arg(argv[i]))
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putendl_fd(": invalid parameter name", 2);
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
