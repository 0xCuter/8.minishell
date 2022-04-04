/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:35:46 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/04 16:06:00 by vvandenb         ###   ########.fr       */
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
void	init_heredoc(t_command *cmd, char **current_token)
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
void	init_append(t_command *cmd, char **current_token)
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
void	init_redir_stdin(t_command *cmd, char **current_token)
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
void	init_redir_stdout(t_command *cmd, char **current_token)
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
