/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:14:15 by scuter            #+#    #+#             */
/*   Updated: 2022/03/22 21:11:38 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// Print the full filename of the current working directory.
int	pwd_cmd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		free(pwd);
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
