/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:06:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/04 22:24:05 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_data *data, int exit_flag)
{
	static char	*str;
	char		*tmp;
	int			len;
	int			slash;

	if (exit_flag)
	{
		free(str);
		return ;
	}
	if (data)
	{
		if (str)
		{
			free(str);
			str = NULL;
		}
		tmp = get_env(data, "USER");
		if (!tmp)
			error("GETENV");
		str = mod_strjoin(str, "\e[1;31m");
		str = mod_strjoin(str, tmp);
		str = mod_strjoin(str, "\e[1;33m@42\e[1;32mNice\e[0m:\e[1;36m");
		tmp = getcwd(NULL, 0);
		len = ft_strlen(tmp);
		slash = 0;
		while (len && slash < 3)
		{
			len--;
			if (tmp[len] == '/')
				slash++;
		}
		str = mod_strjoin(str, &tmp[len]);
		str = mod_strjoin(str, "\e[0m$ ");
		free(tmp);
	}
	ft_putstr_fd(str, 1);
}

//Reads line indefinitely
static void	loop_prompt(t_data *data)
{
	char	*line;
	char	*syntax_error;
	t_list	*c_list;

	while (1)
	{
		prompt(data, 0);
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
	setup_signals();
	loop_prompt(&data);
}
