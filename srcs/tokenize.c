/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:59:11 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/02 15:40:55 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Inits the argument list, or adds an argument
static void	add_arg(t_command *cmd, char *arg)
{
	if (cmd->argv == NULL)
	{
		cmd->argv = ft_calloc(2, sizeof(char *));
		cmd->argv[0] = arg;
	}
	else
	{
		cmd->argv = add_line(arg, cmd->argv);
		free(arg);
	}
}

//Adds the current token to the command argv list
//Also replaces the environment variables and quotes in that token
static void	add_argv(t_command *cmd, char **current_token, t_data *data)
{
	char	*arg;
	int		i;
	int		arg_len;

	arg_len = ft_str_chrset_ign_quotes(*current_token, METACHARS_NO_QUOTES) - (*current_token);
	arg = ft_substr(*current_token, 0, arg_len);
	*current_token += arg_len;
	i = 0;
	while (arg && arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
			replace_quotes(&arg, data, &i);
		else
			++i;
	}
	if (arg[0] == 0)
		free(arg);
	else
		add_arg(cmd, arg);
}

//Inits a new structure representing a command to execute
static t_command	*init_cmd(char *syntax_error, char **current_token, t_data *data, int **last_pipe)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	while (**current_token && *current_token < syntax_error)
	{
		if ((*current_token)[0] == '|')
		{
			init_pipe(cmd, current_token, last_pipe);
			if (*last_pipe)
				break ;
		}
		else if ((*current_token)[0] == '<' && (*current_token)[1] == '<')
			init_heredoc(cmd, current_token);
		else if ((*current_token)[0] == '>' && (*current_token)[1] == '>')
			init_append(cmd, current_token);
		else if ((*current_token)[0] == '<')
			init_redir_stdin(cmd, current_token);
		else if ((*current_token)[0] == '>')
			init_redir_stdout(cmd, current_token);
		else
			add_argv(cmd, current_token, data);
		if (*current_token)
			*current_token = ft_str_chrset_rev(*current_token, METACHARS_WHITE_SPACES);
	}
	return (cmd);
}

//Returns a list of commands
t_list	*tokenize(char *line, t_data *data, char *syntax_error)
{
	char	*current_token;
	t_list	*c_list;
	int		*last_pipe;

	c_list = NULL;
	last_pipe = NULL;
	current_token = ft_str_chrset_rev(line, METACHARS);
	while (current_token && current_token < syntax_error)
	{
		ft_lstadd_back(&c_list, ft_lstnew(init_cmd(syntax_error, &current_token, data, &last_pipe)));
		if (current_token)
			current_token = ft_str_chrset_rev(current_token, METACHARS_WHITE_SPACES);
	}
	return (c_list);
}
