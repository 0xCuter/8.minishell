/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:01:52 by scuter            #+#    #+#             */
/*   Updated: 2022/04/01 01:48:56 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envs(t_data *data, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	data->envs = malloc(sizeof(char *) * (i + 1));
	if (data->envs == NULL)
		error("MALLOC");
	i = 0;
	while (envp[i])
	{
		data->envs[i] = ft_strdup(envp[i]);
		i++;
	}
	data->envs[i] = NULL;
}

void	init_path_split(t_data *data)
{
	char	*path;

	path = get_env(data, "PATH");
	if (path == NULL)
		error("GETENV");
	data->path_split = ft_split(path, ':');
	if (data->path_split == NULL)
		error("MALLOC");
}
