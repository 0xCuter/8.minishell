/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:03:34 by scuter            #+#    #+#             */
/*   Updated: 2022/03/22 22:14:16 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Write arguments to the standard output separated by
// a single space character and followed by a newline.
// Option -n:	do not append a newline.
void	echo_cmd(char **argv)
{
	int	n_flag;
	int i;

	n_flag = 0;
	i = 1;
	while (argv[i] && !ft_strcmp("-n", argv[i]))
	{
		n_flag = 1;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		i++;
			if (argv[i])
		printf(" ");
	}
	if (!n_flag)
		printf("\n");
}
