/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:06:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/01 02:49:00 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_child_pid;

static void	prompt(t_data *data)
{
	char	*tmp;
	int		len;
	int		slash;

	tmp = get_env(data, "USER");
	if (!tmp)
		error("GETENV");
	printf("\e[1;31m%s\e[1;33m@42\e[1;32mNice\e[0m:", tmp);
	tmp = getcwd(NULL, 0);
	len = ft_strlen(tmp);
	slash = 0;
	while (len && slash < 3)
	{
		len--;
		if (tmp[len] == '/')
			slash++;
	}
	printf("\e[1;36m%s\e[0m$ ", &tmp[len]);
	free(tmp);
}

//Reads line indefinitely
static void	loop_prompt(t_data *data)
{
	char	*line;
	char	*syntax_error;
	t_list	*c_list;

	while (1)
	{
		prompt(data);
		line = readline(NULL);
		add_history(line);
		if (line == NULL)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			exit(0);
		}
		syntax_error = check_syntax(line);
		c_list = tokenize(line, data, syntax_error);
		exec_cmd_list(c_list, data);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 || argv[1])
		error("ARGUMENTS");
	init_envs(&data, envp);
	init_path_split(&data);
	g_child_pid = 0;
	setup_signals();
	loop_prompt(&data);
}
