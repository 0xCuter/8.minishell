/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:06:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/30 01:56:28 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_child_pid;

static void	prompt(void)
{
	char	*tmp;
	int		len;
	int		slash;

	tmp = getenv("USER");
	if (!tmp)
		error("GETENV");
	printf("%s@:", tmp);
	tmp = getcwd(NULL, 0);
	len = ft_strlen(tmp);
	slash = 0;
	while (len && slash < 3)
	{
		len--;
		if (tmp[len] == '/')
			slash++;
	}
	printf("%s$ ", &tmp[len]);
	free(tmp);
}

//Reads line indefinitely
static void	loop_prompt(t_data *data)
{
	char	*line;

	while (1)
	{
		prompt();
		line = readline(NULL);
		add_history(line);
		if (line == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		line = check_syntax(line, data);
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
	// init_export(&data);
	init_path_split(&data);
	g_child_pid = 0;
	setup_signals();
	loop_prompt(&data);
}
