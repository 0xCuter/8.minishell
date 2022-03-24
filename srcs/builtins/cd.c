/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:09:02 by scuter            #+#    #+#             */
/*   Updated: 2022/03/24 00:32:45 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_cmd(char **argv)
{
	char	*path;

	path = NULL;
	if (!argv[1] || (argv[1] && !ft_strcmp(argv[1], "~")))
		path = getenv("HOME");
	else if (*argv[1] == '$')
		path = getenv(argv[1] + 1);
	else
		path = argv[1];
	if (chdir(path) == -1)
		ft_putendl_fd(strerror(errno), 2);
}
