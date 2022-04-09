/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:06:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/09 14:21:09 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_globs globs;

char	*prompt(t_data *data)
{
	static char	*str = NULL;
	char		*tmp;
	int			len;
	int			slash;

	if (data)
	{
		if (str)
		{
			free(str);
			str = NULL;
		}
		tmp = get_env(data, "USER");
		if (tmp != NULL)
		{
			str = mod_strjoin(str, "\001\e[1;31m\002");
			str = mod_strjoin(str, tmp);
			str = mod_strjoin(str, "\001\e[1;33m\002@42\001\e[1;32m\002Nice\001\e[0m\002:\001\e[1;36m\002");
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
			str = mod_strjoin(str, "\001\e[0m\002$ ");
			free(tmp);
		}
		else
			str = mod_strjoin(str, DEFAULT_PROMPT);
	}
	return (str);
}

static char	*get_last_pipe(char *line)
{
	char	*last_pipe;
	char	*temp;

	last_pipe = ft_strchr(line, '|');
	while (in_quotes(line, last_pipe))
	{
		temp = ft_strchr(last_pipe + 1, '|');
		last_pipe = temp;
	}
	temp = last_pipe;
	while (temp)
	{
		temp = ft_strchr(temp + 1, '|');
		while (in_quotes(line, last_pipe))
		{
			temp = ft_strchr(last_pipe + 1, '|');
			last_pipe = temp;
		}
		if (temp)
			last_pipe = temp;
	}
	return (last_pipe);
}

//Waits for input when a pipe has no argument
//True if it read line
static char	trailing_pipeline(char **line, t_data *data)
{
	char	*temp;
	char	*last_pipe;
	char	*l;
	int		i;

	last_pipe = get_last_pipe(*line);
	if (last_pipe == NULL)
		return (0);
	i = 0;
	temp = get_meta_arg(last_pipe, &i, data);
	if (temp)
	{
		free(temp);
		return (0);
	}
	free_null((void *)&temp);
	l = readline(WAIT_PROMPT);
	if (l == NULL)
	{
		free(l);
		return (0);
	}
	temp = ft_strjoin(*line, " ");
	free(*line);
	*line = ft_strjoin(temp, l);
	free(l);
	free(temp);
	*line = replace_vars(*line, data);
	return (1);
}

//Reads line indefinitely
static void	loop_prompt(t_data *data)
{
	char	*line;
	t_list	*c_list;

	rl_outstream = stderr;
	while (1)
	{
		line = readline(prompt(data));
		if (line == NULL)
		{
			write(STDIN_FILENO, "\b\b  \b\b", 6);
			exit_shell(data->exit_status);
		}
		while (trailing_pipeline(&line, data));
		if (*line != 0)
			add_history(line);
		line = replace_vars(line, data);
		if (check_syntax(line, data) == 0)
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
	globs.last_child = 1;
	globs.heredocing = 0;
	globs.pids = NULL;
	data.exec_name = argv[0];
	init_envs(&data, envp);
	setup_signals();
	loop_prompt(&data);
}
