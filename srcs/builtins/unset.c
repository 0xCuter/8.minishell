/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:36:21 by scuter            #+#    #+#             */
/*   Updated: 2022/03/25 01:47:09 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_index(char *argv, t_data *data)
{
	char	**key;
	int		i;

	if (!data->envs)
		return (-1);
	key = NULL;
	i = 0;
	while (data->envs[i])
	{
		key = ft_split(data->envs[i], '=');
		if (!key)
			error("MALLOC");
		if (!ft_strcmp(argv, key[0]))
		{
			free_tab(key);
			return (i);
		}
		free_tab(key);
		i++;
	}
	return (-1);
}

static void	remove_line(int index, t_data *data)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	while (data->envs[i])
		i++;
	new = malloc(sizeof(char *) * (i));
	i = 0;
	j = 0;
	while (data->envs[i])
	{
		if (i == index)
			i++;
		if (data->envs[i])
		{
			new[j] = ft_strdup(data->envs[i]);
			i++;
			j++;
		}
	}
	new[j] = NULL;
	free_tab(data->envs);
	data->envs = new;
}

void	unset_cmd(char **argv, t_data *data)
{
	int	index;
	int	i;

	if (!argv[1])
		return ;
	i = 1;
	while (argv[i])
	{
		index = get_index(argv[i], data);
		if (index != -1)
			remove_line(index, data);
		else
			{
				ft_putstr_fd("unset: ", 2);
				ft_putstr_fd(argv[i], 2);
				ft_putendl_fd(": invalid parameter name", 2);
			}
		i++;
	}
}
