/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:59:11 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/29 11:11:04 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_pipe(t_command *cmd, char **current_token, int **last_pipe)
{
	if (*last_pipe == NULL)
	{
		cmd->write_pipe = malloc(2 * sizeof(int));
		*last_pipe = cmd->write_pipe;
		if (pipe(cmd->write_pipe))
			error("PIPE");
	}
	else
	{
		cmd->read_pipe = *last_pipe;
		++*current_token;
		*last_pipe = NULL;
	}
}

static void	init_heredoc(t_command *cmd, char **current_token)
{
	char	*l;
	char	*meta_arg;
	int		meta_length;

	++*current_token;
	meta_arg = get_meta_arg(*current_token, &meta_length);
	if (meta_arg == NULL)
		return ;
	cmd->redir_stdin = malloc(2 * sizeof(int));
	if (pipe(cmd->redir_stdin) == -1)
		error("PIPE");
	while (1)
	{
		l = readline(WAIT_PROMPT);
		if (l == NULL || !ft_strcmp(l, meta_arg))
			break ;
		ft_putendl_fd(l, cmd->redir_stdin[1]);
		free(l);
	}
	free(l);
	free(meta_arg);
	close(cmd->redir_stdin[1]);
	*current_token += meta_length;
}

static void	init_append(t_command *cmd, char **current_token)
{
	(void)cmd;
	(void)current_token;
	// while ()
	// {

	// }
	++*current_token;
	++*current_token;
}

static void	init_redir_stdin(t_command *cmd, char **current_token)
{
	(void)cmd;
	(void)current_token;
	// while ()
	// {

	// }
	++*current_token;
}

static void	init_redir_stdout(t_command *cmd, char **current_token)
{
	(void)cmd;
	(void)current_token;
	// while ()
	// {

	// }
	++*current_token;
}

static void	add_argv(t_command *cmd, char **current_token)
{
	int		arg_size;
	char	*temp;
	char	*temp_bis;

	arg_size = ft_str_chrset(*current_token, METACHARS) - *current_token;
	if (cmd->args == NULL)
		cmd->args = ft_substr(*current_token, 0, arg_size);
	else
	{
		temp = ft_substr(*current_token, 0, arg_size);
		temp_bis = ft_strjoin(" ", temp);
		free(temp);
		temp = cmd->args;
		cmd->args = ft_strjoin(cmd->args, temp_bis);
		free(temp);
		free(temp_bis);
	}
	*current_token += arg_size;
}

static t_command	*init_cmd(int id, char **current_token, t_data *data, int **last_pipe)
{
	(void)data;
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	cmd->id = id;
	while (**current_token)
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
			add_argv(cmd, current_token);
		if (*current_token)
			*current_token = ft_str_chrset_rev(*current_token, METACHARS_WHITE_SPACES);
	}
	return (cmd);
}

//Returns a list of commands (which are a list of tokens)
t_list	*tokenize(char *line, t_data *data, char *syntax_error)
{
	char	*current_token;
	t_list	*c_list;
	int		*last_pipe;
	int		id;

	c_list = NULL;
	last_pipe = NULL;
	id = 0;
	current_token = ft_str_chrset_rev(line, METACHARS);
	while (current_token && current_token < syntax_error)
	{
		ft_lstadd_back(&c_list, ft_lstnew(init_cmd(id, &current_token, data, &last_pipe)));
		if (current_token)
			current_token = ft_str_chrset_rev(current_token, METACHARS_WHITE_SPACES);
		++id;
	}
	return (c_list);
}
