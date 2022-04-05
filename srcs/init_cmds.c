/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:59:11 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/05 11:20:02 by vvandenb         ###   ########.fr       */
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
static void	add_argv(t_command *cmd, char **cur_char, t_data *data)
{
	char	*arg;
	int		i;
	int		arg_len;

	arg_len = ft_str_chrset_ign_quotes(*cur_char,
			METACHARS_NO_QUOTES) - (*cur_char);
	arg = ft_substr(*cur_char, 0, arg_len);
	*cur_char += arg_len;
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

//Inits a new `t_command` structure
static t_command	*init_cmd(char **cur_char, t_data *data, char *stdout_pipe)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	while (**cur_char)
	{
		if ((*cur_char)[0] == '|')
		{
			if (init_pipe(cmd, stdout_pipe, cur_char))
				break ;
		}
		else if ((*cur_char)[0] == '<' && (*cur_char)[1] == '<')
			init_heredoc(cmd, cur_char);
		else if ((*cur_char)[0] == '>' && (*cur_char)[1] == '>')
			init_append(cmd, cur_char);
		else if ((*cur_char)[0] == '<')
			init_redir_stdin(cmd, cur_char);
		else if ((*cur_char)[0] == '>')
			init_redir_stdout(cmd, cur_char);
		else
			add_argv(cmd, cur_char, data);
		if (*cur_char)
			*cur_char = ft_str_chrset_rev(*cur_char, METACHARS_WHITE_SPACES);
	}
	return (cmd);
}

//Returns a list of struct representing commands to execute
t_list	*init_cmds(char *line, t_data *data)
{
	char		*cur_char;
	t_command	*cmd;
	t_list		*c_list;
	char		stdout_pipe;
	int			cmd_id;

	c_list = NULL;
	stdout_pipe = 1;
	cmd_id = 0;
	cur_char = ft_str_chrset_rev(line, METACHARS);
	while (cur_char && *cur_char)
	{
		cmd = init_cmd(&cur_char, data, &stdout_pipe);
		cmd->id = cmd_id++;
		ft_lstadd_back(&c_list, ft_lstnew(cmd));
		if (cur_char)
			cur_char = ft_str_chrset_rev(cur_char, METACHARS_WHITE_SPACES);
	}
	return (c_list);
}
