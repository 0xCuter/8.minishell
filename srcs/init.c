/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:01:52 by scuter            #+#    #+#             */
/*   Updated: 2022/04/05 12:52:25 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Only inits `data->envs` with `DEFAULT_PATH`
static void	init_envs_default(t_data *data)
{
	data->envs = malloc(sizeof(char *) * 2);
	if (data->envs == NULL)
		error("MALLOC");
	data->envs[0] = ft_strdup(DEFAULT_PATH);
	if (data->envs[0] == NULL)
		error("MALLOC");
	data->envs[1] = NULL;
}

//If `envp` is not empty, inits `data->envs` with its data
void	init_envs(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	if (i == 0)
	{
		init_envs_default(data);
		return ;
	}
	data->envs = malloc(sizeof(char *) * (i + 1));
	if (data->envs == NULL)
		error("MALLOC");
	i = 0;
	while (envp[i])
	{
		data->envs[i] = ft_strdup(envp[i]);
		if (data->envs[i] == NULL)
			error("MALLOC");
		i++;
	}
	data->envs[i] = NULL;
}

//Inits the `path_split` in `data`
void	init_path_split(t_data *data)
{
	char	*path;

	path = get_env(data, "PATH");
	if (path == NULL)
		return ;
	data->path_split = ft_split(path, ':');
	if (data->path_split == NULL)
		error("MALLOC");
}
