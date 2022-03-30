/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:26:38 by scuter            #+#    #+#             */
/*   Updated: 2022/03/30 02:10:23 by scuter           ###   ########.fr       */
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
	while(argv[i] && argv[i] != '=')
	{
		if (!ft_isalnum(argv[i]) && argv[i]!= '_')
			return(1);
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
	char *envar;
	int i;

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
			ft_putstr_fd("export: not valid in this context: ", 2);
			ft_putstr_fd(argv[i], 2);
		}
		else
		{
			envar = find_envar(data, argv[i]);
			if (!envar)
				data->envs = add_line(argv[i], data->envs);
			else if (ft_strchr(argv[i], '='))
			{
				free(envar);
				envar = ft_strdup(argv[i]);
			}
		}
		i++;
	}
}
