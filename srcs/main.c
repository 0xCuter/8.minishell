/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:06:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/28 18:16:57 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_child_pid;

//Reads line indefinitely
static void	loop_prompt(t_data *data)
{
	char	*line;
	char	*syntax_error;
	t_list	*c_list;

	while (1)
	{
		line = readline(PROMPT);
		add_history(line);
		if (line == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		syntax_error = check_syntax(line, data);
		c_list = tokenize(line, data, syntax_error);
		execute_cmd_list(c_list, data);
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
	setup_signals();
	loop_prompt(&data);
}
