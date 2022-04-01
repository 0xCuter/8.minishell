/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:35:46 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/31 14:37:02 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//|
void	init_pipe(t_command *cmd, char **current_token, int **last_pipe)
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
