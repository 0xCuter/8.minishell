/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:35:46 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/08 18:35:35 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//|
char	init_pipe(t_command *cmd, char *stdout_pipe, char **cur_char)
{
	if (*stdout_pipe)
	{
		cmd->stdout_piped = 1;
		*stdout_pipe = 0;
		return (1);
	}
	else
	{
		cmd->stdin_piped = 1;
		*stdout_pipe = 1;
		++*cur_char;
	}
	return (0);
}

//<<
char	init_heredoc(t_command *cmd, char **cur_char, t_data *data)
{
	char	*l;
	char	*meta_arg;
	int		meta_length;
	int		stdin_copy;

	stdin_copy = dup(STDIN_FILENO);
	signal(SIGINT, (void *)heredoc_signal);
	++*cur_char;
	meta_arg = get_meta_arg(*cur_char, &meta_length, data);
	if (meta_arg == NULL)
		return (1);
	cmd->redir_stdin = malloc(2 * sizeof(int));
	if (cmd->redir_stdin == NULL)
	{
		free(meta_arg);
		return (1);
	}
	if (pipe(cmd->redir_stdin) == -1)
		error("PIPE");
	while (1)
	{
		l = readline(WAIT_PROMPT);
		if (l == NULL || !ft_strcmp(l, meta_arg))
		{
			dup2(stdin_copy, STDIN_FILENO);
			close(stdin_copy);
			free(l);
			free(meta_arg);
			close(cmd->redir_stdin[1]);
			*cur_char += meta_length;
			return (1);
		}
		ft_putendl_fd(l, cmd->redir_stdin[1]);
		free(l);
	}
	free(l);
	free(meta_arg);
	close(cmd->redir_stdin[1]);
	*cur_char += meta_length;
	return (0);
}

//>>
void	init_append(t_command *cmd, char **cur_char, t_data *data)
{
	char	*meta_arg;
	int		meta_length;

	++*cur_char;
	meta_arg = get_meta_arg(*cur_char, &meta_length, data);
	if (meta_arg == NULL)
		return ;
	cmd->redir_stdout = malloc(sizeof(int));
	if (cmd->redir_stdout == NULL)
		return ;
	*cmd->redir_stdout = open(meta_arg, O_WRONLY | O_CREAT | O_APPEND, 0777);
	free(meta_arg);
	if (*cmd->redir_stdout == -1)
		error("OPEN");
	*cur_char += meta_length;
}

//<
char	init_redir_stdin(t_command *cmd, char **cur_char, t_data *data)
{
	char	*meta_arg;
	int		meta_length;
	int		r;

	r = 0;
	meta_arg = get_meta_arg(*cur_char, &meta_length, data);
	if (meta_arg == NULL)
		return (1);
	cmd->redir_stdin = malloc(sizeof(int));
	if (cmd->redir_stdin == NULL)
		return (1);
	*cmd->redir_stdin = open(meta_arg, O_RDONLY);
	if (*cmd->redir_stdin == -1)
	{
		free(cmd->redir_stdin);
		cmd->redir_stdin = NULL;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(meta_arg);
		r = 1;
	}
	free(meta_arg);
	*cur_char += meta_length;
	return (r);
}

//>
char	init_redir_stdout(t_command *cmd, char **cur_char, t_data *data)
{
	char	*meta_arg;
	int		meta_length;
	int		r;

	r = 0;
	meta_arg = get_meta_arg(*cur_char, &meta_length, data);
	if (meta_arg == NULL)
		return (1);
	cmd->redir_stdout = malloc(sizeof(int));
	if (cmd->redir_stdout == NULL)
		return (1);
	unlink(meta_arg);
	*cmd->redir_stdout = open(meta_arg, O_WRONLY | O_CREAT, 0777);
	if (*cmd->redir_stdout == -1)
	{
		free(cmd->redir_stdout);
		cmd->redir_stdout = NULL;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(meta_arg);
		r = 1;
	}
	free(meta_arg);
	*cur_char += meta_length;
	return (r);
}
