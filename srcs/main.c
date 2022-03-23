/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:06:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/23 11:07:05 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Reads line indefinitely
static void	loop_prompt(char **path_split)
{
	char		*line;

	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
		{
			printf("\n");
			exit(0);
		}
		execute(line, path_split);
	}
}

int	main(void)
{
	char	*path;
	char	**path_split;

	path = getenv("PATH");
	if (path == NULL)
		return (1);
	path_split = ft_split(path, ':');
	if (path_split == NULL)
		error("MALLOC");
	g_child_pid = 0;
	setup_signals();
	loop_prompt(path_split);
}
