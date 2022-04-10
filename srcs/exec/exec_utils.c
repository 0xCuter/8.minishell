/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 14:40:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/10 08:20:47 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Redirects stdin or stdout
//If `old_stdin` or `old_stdout`, also saves the old stdin or stdout
void	setup_redirs(t_command *cmd, int *old_stdin, int *old_stdout)
{
	if (cmd->redir_stdin)
	{
		if (old_stdin)
			*old_stdin = dup(STDIN_FILENO);
		if (dup2(cmd->redir_stdin[0], STDIN_FILENO) == -1)
			error("DUP2");
		if (close(cmd->redir_stdin[0]) == -1)
			error("CLOSE");
		free_null((void *)&cmd->redir_stdin);
	}
	if (cmd->redir_stdout)
	{
		if (old_stdout)
			*old_stdout = dup(STDOUT_FILENO);
		if (dup2(*cmd->redir_stdout, STDOUT_FILENO) == -1)
			error("DUP2");
		if (close(*cmd->redir_stdout) == -1)
			error("CLOSE");
		free_null((void *)&cmd->redir_stdout);
	}
}

//`data->exit_status` is set to `error`
//`s1` and `s2` get printed
//`free()` is called on `s2`
//Returns NULL
char	*error_ret_null(t_data *data, int error, char *s1, char *s2)
{
	data->exit_status = error;
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putendl_fd(s2, STDERR_FILENO);
	free(s2);
	return (NULL);
}
