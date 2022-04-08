/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:26:38 by scuter            #+#    #+#             */
/*   Updated: 2022/04/08 13:25:06 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_export_arg(char *argv)
{
	int	i;

	i = 0;
	if (!ft_isalpha(argv[i]) && argv[i] != '_')
		return (1);
	i++;
	while (argv[i] && argv[i] != '=')
	{
		if (!ft_isalnum(argv[i]) && argv[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static void	print_export(char **envs)
{
	char	**export;
	int		i;
	int		j;
	int		equal;

	export = duplicate_tab(envs);
	sort_tab(export);
	i = 0;
	while (export[i])
	{
		ft_putstr_fd("declare -x ", 1);
		j = 0;
		equal = 0;
		while (export[i][j])
		{
			ft_putchar_fd(export[i][j], 1);
			if (export[i][j] == '=' && !equal)
			{
				ft_putchar_fd('"', 1);
				equal = 1;
			}
			j++;
		}
		if (equal)
			ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	free(export);
}

void	export_cmd(char **argv, t_data *data)
{
	char	*envar;
	int		i;

	data->exit_status = 0;
	if (!argv[1])
	{
		print_export(data->envs);
		return ;
	}
	i = 1;
	while (argv[i])
	{
		if (check_export_arg(argv[i]))
		{
			data->exit_status = 1;
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		else
		{
			envar = find_key(data, argv[i]);
			if (!envar)
				data->envs = add_line(argv[i], data->envs);
			else if (ft_strchr(argv[i], '='))
				replace_env(data, envar, argv[i]);
		}
		i++;
	}
}
