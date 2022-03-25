/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:06:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/25 01:36:34 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_child_pid;

//Reads line indefinitely
static void	loop_prompt(t_data *data)
{
	char		*line;

	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		execute(data, line);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 || argv[1])
		error("ARGUMENTS");
	init_envs(&data, envp);
	// init_envs_export(&data);
	init_path_split(&data);
	g_child_pid = 0;
	setup_signals(0);
	loop_prompt(&data);
}
