/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:06:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/03 15:05:08 by vvandenb         ###   ########.fr       */
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
	ft_putstr_fd("\e[1;31m", 1);
	ft_putstr_fd(tmp, 1);
	ft_putstr_fd("\e[1;33m@42\e[1;32mNice\e[0m:", 1);
	tmp = getcwd(NULL, 0);
	len = ft_strlen(tmp);
	slash = 0;
	while (len && slash < 3)
	{
		len--;
		if (tmp[len] == '/')
			slash++;
	}
	ft_putstr_fd("\e[1;36m", 1);
	ft_putstr_fd(&tmp[len], 1);
	ft_putstr_fd("\e[0m$ ", 1);
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
		line = replace_vars(line, data);
		syntax_error = check_syntax(line);
		c_list = init_cmds(line, data, syntax_error);
		free(line);
		exec_cmd_list(c_list, data);
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
