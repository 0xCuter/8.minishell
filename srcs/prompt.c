/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:30:15 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/09 17:47:37 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_prompt(char *user_var, char **prompt)
{
	char	*cwd;
	int		len;
	int		slash;

	if (user_var != NULL)
	{
		*prompt = mod_strjoin(*prompt, "\001\e[1;31m\002");
		*prompt = mod_strjoin(*prompt, user_var);
		*prompt = mod_strjoin(*prompt, PROMPT_HEAD);
		cwd = getcwd(NULL, 0);
		len = ft_strlen(cwd);
		slash = 0;
		while (len && slash < 3)
		{
			len--;
			if (cwd[len] == '/')
				slash++;
		}
		*prompt = mod_strjoin(*prompt, cwd + len);
		*prompt = mod_strjoin(*prompt, "\001\e[0m\002$ ");
		free(cwd);
	}
	else
		*prompt = mod_strjoin(*prompt, DEFAULT_PROMPT);
	return (*prompt);
}

//Returns the prompt string
char	*prompt(t_data *data)
{
	static char	*prompt = NULL;

	if (data)
	{
		if (prompt)
		{
			free(prompt);
			prompt = NULL;
		}
		create_prompt(get_env(data, "USER"), &prompt);
	}
	return (prompt);
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
//True if it read a line
char	trailing_pipeline(char **line, t_data *data)
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
		return (free_ret(temp, 0));
	free_null((void *)&temp);
	l = readline(WAIT_PROMPT);
	if (l == NULL)
		return (free_ret(l, 0));
	temp = ft_strjoin(*line, " ");
	free(*line);
	*line = ft_strjoin(temp, l);
	free(l);
	free(temp);
	*line = replace_vars(*line, data);
	return (1);
}
