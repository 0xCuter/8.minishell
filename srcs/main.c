/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:06:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/30 09:51:31 by vvandenb         ###   ########.fr       */
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
	char	*syntax_error;
	t_list	*c_list;

	while (1)
	{
		prompt();
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
	// init_export(&data);
	init_path_split(&data);
	g_child_pid = 0;
	setup_signals();
	loop_prompt(&data);
}
