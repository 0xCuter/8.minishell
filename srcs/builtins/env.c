/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:23:35 by scuter            #+#    #+#             */
/*   Updated: 2022/04/08 16:53:31 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(t_data *data)
{
	int	i;

	data->exit_status = 0;
	i = 0;
	while (data->envs[i])
	{
		if (ft_strchr(data->envs[i], '='))
			ft_putendl_fd(data->envs[i], 1);
		i++;
	}
}
