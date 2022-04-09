/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:35:46 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/09 14:29:44 by vvandenb         ###   ########.fr       */
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
			if (g_globs.heredocing)
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
	cmd->redir_stdin = malloc(2 * sizeof(int));
	if (cmd->redir_stdin == NULL)
	{
		*cur_char += meta_length;
		free(meta_arg);
		return (1);
	}
	if (pipe(cmd->redir_stdin) == -1)
		error("PIPE");
	r = init_heredoc_bis(cmd, meta_arg);
	setup_signals();
	g_globs.heredocing = 0;
	free(meta_arg);
	close(cmd->redir_stdin[1]);
	*cur_char += meta_length;
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
	cmd->redir_stdout = malloc(sizeof(int));
	if (cmd->redir_stdout == NULL)
		return (1);
	*cmd->redir_stdout = open(meta_arg, O_WRONLY | O_CREAT | O_APPEND, 0777);
	r = 0;
	if (*cmd->redir_stdout == -1)
	{
		free(cmd->redir_stdout);
		cmd->redir_stdout = NULL;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(meta_arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror(meta_arg);
		r = 1;
	}
	free(meta_arg);
	*cur_char += meta_length;
	return (r);
}

//<
char	init_redir_stdin(t_command *cmd, char **cur_char, t_data *data)
{
	char	*meta_arg;
	int		meta_length;
	int		r;

	*cur_char += 1;
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

	*cur_char += 1;
	r = 0;
	meta_arg = get_meta_arg(*cur_char, &meta_length, data);
	if (meta_arg == NULL)
	{
		ft_putendl_fd("minishell: : No such file or directory", STDERR_FILENO);
		return (1);
	}
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
		ft_putstr_fd(meta_arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror(meta_arg);
		r = 1;
	}
	free(meta_arg);
	*cur_char += meta_length;
	return (r);
}
