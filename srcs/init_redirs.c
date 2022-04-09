/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:35:46 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/09 17:43:30 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	init_heredoc_bis(t_command *cmd, char *meta_arg)
{
	char	r;
	char	*l;
	int		stdin_copy;

	stdin_copy = dup(STDIN_FILENO);
	r = 0;
	signal(SIGINT, (void *)heredoc_signal);
	while (1)
	{
		l = readline(WAIT_PROMPT);
		if (l == NULL || !ft_strcmp(l, meta_arg))
		{
			if (g_globs.heredoc_killed)
			{
				dup2(stdin_copy, STDIN_FILENO);
				r = 1;
			}
			break ;
		}
		ft_putendl_fd(l, cmd->redir_stdin[1]);
		free(l);
	}
	close(stdin_copy);
	free(l);
	return (r);
}

//<<
char	init_heredoc(t_command *cmd, char **cur_char, t_data *data)
{
	char	r;
	char	*meta_arg;
	int		meta_length;

	++*cur_char;
	meta_arg = get_meta_arg(*cur_char, &meta_length, data);
	if (meta_arg == NULL)
		return (1);
	*cur_char += meta_length;
	if (cmd->error_init)
		return (free_ret(meta_arg, 1));
	if (cmd->redir_stdin)
		close_free(cmd->redir_stdin);
	cmd->redir_stdin = malloc(2 * sizeof(int));
	if (cmd->redir_stdin == NULL)
		return (free_ret(meta_arg, 1));
	if (pipe(cmd->redir_stdin) == -1)
		error("PIPE");
	r = init_heredoc_bis(cmd, meta_arg);
	setup_signals();
	g_globs.heredoc_killed = 0;
	free(meta_arg);
	close(cmd->redir_stdin[1]);
	return (r);
}

//>>
char	init_append(t_command *cmd, char **cur_char, t_data *data)
{
	char	*meta_arg;
	int		meta_length;
	char	r;

	++*cur_char;
	meta_arg = get_meta_arg(*cur_char, &meta_length, data);
	if (meta_arg == NULL)
		return (1);
	*cur_char += meta_length;
	if (cmd->error_init)
		return (free_ret(meta_arg, 1));
	if (cmd->redir_stdout)
		close_free(cmd->redir_stdout);
	cmd->redir_stdout = malloc(sizeof(int));
	if (cmd->redir_stdout == NULL)
		return (free_ret(meta_arg, 1));
	*cmd->redir_stdout = open(meta_arg, O_WRONLY | O_CREAT | O_APPEND, 0777);
	r = 0;
	if (*cmd->redir_stdout == -1)
		error_open(&cmd->redir_stdout, meta_arg, &r);
	free(meta_arg);
	return (r);
}

//<
char	init_redir_stdin(t_command *cmd, char **cur_char, t_data *data)
{
	char	*meta_arg;
	int		meta_length;
	char	r;

	meta_arg = get_meta_arg(*cur_char, &meta_length, data);
	if (meta_arg == NULL)
		return (1);
	*cur_char += meta_length;
	if (cmd->error_init)
		return (free_ret(meta_arg, 1));
	if (cmd->redir_stdin)
		close_free(cmd->redir_stdin);
	cmd->redir_stdin = malloc(sizeof(int));
	if (cmd->redir_stdin == NULL)
		return (free_ret(meta_arg, 1));
	*cmd->redir_stdin = open(meta_arg, O_RDONLY);
	r = 0;
	if (*cmd->redir_stdin == -1)
		error_open(&cmd->redir_stdin, meta_arg, &r);
	free(meta_arg);
	return (r);
}

//>
char	init_redir_stdout(t_command *cmd, char **cur_char, t_data *data)
{
	char	*meta_arg;
	int		meta_length;
	char	r;

	meta_arg = get_meta_arg(*cur_char, &meta_length, data);
	if (meta_arg == NULL)
		return (1);
	*cur_char += meta_length;
	if (cmd->error_init)
		return (free_ret(meta_arg, 1));
	if (cmd->redir_stdout)
		close_free(cmd->redir_stdout);
	cmd->redir_stdout = malloc(sizeof(int));
	if (cmd->redir_stdout == NULL)
		return (free_ret(meta_arg, 1));
	unlink(meta_arg);
	*cmd->redir_stdout = open(meta_arg, O_WRONLY | O_CREAT, 0777);
	r = 0;
	if (*cmd->redir_stdout == -1)
		error_open(&cmd->redir_stdout, meta_arg, &r);
	free(meta_arg);
	return (r);
}
