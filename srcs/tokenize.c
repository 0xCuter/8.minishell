/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:59:11 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/30 13:50:03 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//|
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

//<<
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

//>>
static void	init_append(t_command *cmd, char **current_token)
{
	char	*meta_arg;
	int		meta_length;

	++*current_token;
	meta_arg = get_meta_arg(*current_token, &meta_length);
	if (meta_arg == NULL)
		return ;
	cmd->redir_stdout = malloc(sizeof(int));
	*cmd->redir_stdout = open(meta_arg, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (*cmd->redir_stdout == -1)
		error("OPEN");
	free(meta_arg);
	*current_token += meta_length;
}

//<
static void	init_redir_stdin(t_command *cmd, char **current_token)
{
	char	*meta_arg;
	int		meta_length;

	meta_arg = get_meta_arg(*current_token, &meta_length);
	if (meta_arg == NULL)
		return ;
	cmd->redir_stdin = malloc(sizeof(int));
	*cmd->redir_stdin = open(meta_arg, O_RDONLY);
	if (*cmd->redir_stdin == -1)
		error("OPEN");
	free(meta_arg);
	*current_token += meta_length;
}

//>
static void	init_redir_stdout(t_command *cmd, char **current_token)
{
	char	*meta_arg;
	int		meta_length;

	meta_arg = get_meta_arg(*current_token, &meta_length);
	if (meta_arg == NULL)
		return ;
	cmd->redir_stdout = malloc(sizeof(int));
	*cmd->redir_stdout = open(meta_arg, O_WRONLY | O_CREAT, 0777);
	if (*cmd->redir_stdout == -1)
		error("OPEN");
	free(meta_arg);
	*current_token += meta_length;
}

static char	*get_arg(char **current_token, t_data *data)
{
	char	*arg;
	int		arg_size;
	int		i = 0;

	if ((*current_token)[0] == '$' && ft_strchr(METACHARS_WHITE_SPACES, (*current_token)[1]) == NULL)
	{
		arg_size = ft_str_chrset(*current_token + 1, METACHARS) - *current_token;
		arg = ft_substr(*current_token, 0, arg_size);
		arg = replace_var(arg, data, &i);
	}
	else if ((*current_token)[0] == '"' || (*current_token)[0] == '\'')
	{
		arg_size = ft_strchr(*current_token + 1, (*current_token)[0]) - *current_token + 1;
		arg = ft_substr(*current_token, 0, arg_size);
		replace_quotes(&arg, data);
	}
	else
	{
		arg_size = ft_str_chrset(*current_token, METACHARS) - *current_token;
		arg = ft_substr(*current_token, 0, arg_size);
	}
	*current_token += arg_size;
	return (arg);
}

//Inits the argument list, or adds an argument
static void	add_argv(t_command *cmd, char **current_token, t_data *data)
{
	char	*arg;

	arg = get_arg(current_token, data);
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

//Returns a list of commands (which are a list of tokens)
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
