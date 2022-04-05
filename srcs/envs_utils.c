/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:32:05 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/05 12:28:59 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Returns the address of the var string if the `var_name`is found
//Else NULL
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
			{
				free(envar);
				return (*env);
			}
			free(envar);
		}
		else if (!ft_strcmp(var_name, *env))
			return (*env);
		++env;
	}
	return (NULL);
}

//Returns the address of the var string if the key of 'str' is found
//Else NULL
char	*find_key(t_data *data, char *str)
{
	char	*key;
	char	*equal;
	char	*envar;

	equal = ft_strchr(str, '=');
	if (equal)
	{
		key = ft_substr(str, 0, equal - str);
		envar = find_envar(data, key);
		free(key);
	}
	else
		envar = find_envar(data, str);
	return (envar);
}

//Returns a pointer to the env value if the 'key' is found
//Else NULL
char	*get_env(t_data *data, char *key)
{
	char	*envar;

	envar = find_envar(data, key);
	if (envar)
		return (ft_strchr(envar, '=') + 1);
	return (NULL);
}

void	replace_env(t_data *data, char *envar, char *line)
{
	int	i;

	i = 0;
	while (data->envs[i])
	{
		if (data->envs[i] == envar)
		{
			free(data->envs[i]);
			data->envs[i] = ft_strdup(line);
			return ;
		}
		i++;
	}
}
