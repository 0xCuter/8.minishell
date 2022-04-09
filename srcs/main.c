/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:06:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/09 17:30:10 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_globs	g_globs;

//Reads line indefinitely
static void	loop_prompt(t_data *data)
{
	char	*line;
	t_list	*c_list;

	while (1)
	{
		line = readline(prompt(data));
		if (line == NULL)
			exit_shell(data->exit_status, 1);
		while (trailing_pipeline(&line, data))
			;
		if (*line != 0)
			add_history(line);
		line = replace_vars(line, data);
		if (line != NULL && check_syntax(line, data) == 0)
		{
			c_list = init_cmds(line, data);
			free(line);
			exec_cmd_list(c_list, data);
		}
		else
			free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 || argv[1])
	{
		ft_putendl_fd("Minishell requires no arguments", STDERR_FILENO);
		exit(2);
	}
	rl_catch_signals = 0;
	rl_outstream = stderr;
	g_globs.last_child = 1;
	g_globs.heredoc_killed = 0;
	g_globs.pids = NULL;
	data.exit_status = 0;
	data.exec_name = argv[0];
	init_envs(&data, envp);
	setup_signals();
	loop_prompt(&data);
}
