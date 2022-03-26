/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:32:05 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/26 15:34:48 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_envar(t_data *data, char *var_name)
{
	char	**env;
	char	*envar;
	char	*envar_equal;

	env = data->envs;
	while (*env)
	{
		envar_equal = ft_strchr(*env, '=');
		if (envar_equal != NULL)
		{
			envar = ft_substr(*env, 0, envar_equal - *env);
			if (!ft_strcmp(var_name, envar))
				return (*env);
		}
		++env;
	}
	return (NULL);
}
