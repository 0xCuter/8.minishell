/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:09:02 by scuter            #+#    #+#             */
/*   Updated: 2022/03/30 00:29:48 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Change the working directory of the current shell execution environmen.
void	cd_cmd(char **argv)
{
	char	*path;

	path = NULL;
	if (!argv[1] || (!ft_strcmp(argv[1], "~")) || (!ft_strcmp(argv[1], "--")))
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return ;
		}
	}
	else if (*argv[1] == '$')
		path = getenv(argv[1] + 1);
	else
		path = argv[1];
	if (chdir(path) == -1)
		ft_putendl_fd(strerror(errno), 2);
}
