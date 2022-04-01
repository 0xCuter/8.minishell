/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:09:02 by scuter            #+#    #+#             */
/*   Updated: 2022/04/01 02:01:59 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Change the working directory of the current shell execution environment.
void	cd_cmd(char **argv, t_data *data)
{
	char	*path;

	path = NULL;
	if (argv && argv[1] && argv[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return ;
	}
	if (!argv[1] || (!ft_strcmp(argv[1], "~")) || (!ft_strcmp(argv[1], "--")))
	{
		path = get_env(data, "HOME");
		if (!path)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return ;
		}
	}
	// else if (*argv[1] == '$')
	// 	path = get_env(data, argv[1] + 1);
	else
		path = argv[1];
	if (chdir(path) == -1)
		ft_putendl_fd(strerror(errno), 2);
}
