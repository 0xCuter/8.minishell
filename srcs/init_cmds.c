/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:59:11 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/10 08:53:53 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_cmd_ter(char **cur, t_data *d, t_command *c)
{
	if ((*cur)[0] == '<' && (*cur)[1] == '<')
	{
		if (init_heredoc(c, cur, d))
			c->error_init = 1;
	}
	else if ((*cur)[0] == '>' && (*cur)[1] == '>')
	{
		if (init_append(c, cur, d))
			c->error_init = 1;
	}
	else if ((*cur)[0] == '<')
	{
		if (init_redir_stdin(c, cur, d))
			c->error_init = 1;
	}
	else if ((*cur)[0] == '>')
	{
		if (init_redir_stdout(c, cur, d))
			c->error_init = 1;
	}
	else
		add_argv(c, cur, d);
}

static char	init_cmd_bis(char **cur, t_data *d, char *stdout_p, t_command *c)
{
	if ((*cur)[0] == '|')
	{
		if (init_pipe(c, stdout_p, cur))
			return (1);
	}
	else
		init_cmd_ter(cur, d, c);
	return (0);
}

//Inits a new `t_command` structure
static t_command	*init_cmd(char **cur_char, t_data *data, char *stdout_pipe)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (cmd == NULL)
		return (NULL);
	while (**cur_char)
	{
		if (init_cmd_bis(cur_char, data, stdout_pipe, cmd))
			break ;
		if (*cur_char && **cur_char)
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
	cur_char = ft_str_chrset_rev(line, METACHARS_WHITE_SPACES);
	data->cmd_count = 0;
	while (cur_char && *cur_char)
	{
		cmd = init_cmd(&cur_char, data, &stdout_pipe);
		if (cmd != NULL)
		{
			++data->cmd_count;
			cmd->id = cmd_id++;
			ft_lstadd_back(&c_list, ft_lstnew(cmd));
		}
	}
	return (c_list);
}
