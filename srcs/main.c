/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:06:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/22 17:42:44 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	loop_prompt(char **path_split)
{
	char	*line;
	char	*command;
	int		pid;

	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
		{
			printf("\n");
			exit(0);
		}
		command = find_command(line, path_split);
		free(line);
		if (command)
			pid = execute(command);
		waitpid(pid, NULL, 0);
		CHILD_PID = 0;
	}
}

int	main()
{
	char	*path;
	char	**path_split;

	path = getenv("PATH");
	if (path == NULL)
		return (1);
	path_split = ft_split(path, ':');
	if (path_split == NULL)
		error("MALLOC");
	CHILD_PID = 0;
	setup_signals();
	loop_prompt(path_split);
}
