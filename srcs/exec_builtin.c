/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:35:45 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/07 18:45:23 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Sets the correct pipes
static void	setup_pipes(t_command *cmd, int *old_stdin, int *old_stdout)
{
	if (cmd->stdin_piped && cmd->redir_stdin == 0)
	{
		*old_stdin = dup(STDIN_FILENO);
		if (*old_stdin == -1)
			error("DUP");
		if (dup2(cmd->stdin_pipe[0], STDIN_FILENO) == -1)
			error("DUP2");
	}
	if (cmd->stdout_piped && cmd->redir_stdout == 0)
	{
		*old_stdout = dup(STDOUT_FILENO);
		if (*old_stdout == -1)
			error("DUP");
		if (dup2(cmd->stdout_pipe[1], STDOUT_FILENO) == -1)
			error("DUP2");
	}
}

//Resets stdin/stdout
static void	reset_pipes(int old_stdin, int old_stdout)
{
	if (old_stdin != -2)
	{
		if (dup2(old_stdin, STDIN_FILENO) == -1)
			error("DUP2");
		if (close(old_stdin) == -1)
			error("CLOSE");
	}
	if (old_stdout != -2)
	{
		if (dup2(old_stdout, STDOUT_FILENO) == -1)
			error("DUP2");
		if (close(old_stdout) == -1)
			error("CLOSE");
	}
}

//Returns 1 if `cmd_name` is a builtin, else 0
char	is_builtin(char *cmd_name)
{
	char	r;

	r = 0;
	if (!ft_strcmp(cmd_name, "echo"))
		r = 1;
	else if (!ft_strcmp(cmd_name, "exit"))
		r = 1;
	else if (!ft_strcmp(cmd_name, "pwd"))
		r = 1;
	else if (!ft_strcmp(cmd_name, "cd"))
		r = 1;
	else if (!ft_strcmp(cmd_name, "env"))
		r = 1;
	else if (!ft_strcmp(cmd_name, "unset"))
		r = 1;
	else if (!ft_strcmp(cmd_name, "export"))
		r = 1;
	return (r);
}

static void	setup_redirs(t_command *cmd, int *old_stdin, int *old_stdout)
{
	if (cmd->redir_stdin)
	{
		*old_stdin = dup(STDIN_FILENO);
		if (dup2(cmd->redir_stdin[0], STDIN_FILENO) == -1)
			error("DUP2");
		if (close(cmd->redir_stdin[0]) == -1)
			error("CLOSE");
		free_null((void *)&cmd->redir_stdin);
	}
	if (cmd->redir_stdout)
	{
		*old_stdout = dup(STDOUT_FILENO);
		if (dup2(*cmd->redir_stdout, STDOUT_FILENO) == -1)
			error("DUP2");
		if (close(*cmd->redir_stdout) == -1)
			error("CLOSE");
		free_null((void *)&cmd->redir_stdin);
	}
}

//Executes a builtin
void	exec_builtin(t_command *cmd, t_data *data, char **argv)
{
	int	old_stdin = -2;
	int	old_stdout = -2;

	setup_pipes(cmd, &old_stdin, &old_stdout);
	setup_redirs(cmd, &old_stdin, &old_stdout);
	if (argv && cmd->error_init == 0)
	{
		if (!ft_strcmp(argv[0], "echo"))
			echo_cmd(argv, data);
		else if (!ft_strcmp(argv[0], "exit") && data->cmd_count == 1)
			exit_cmd(argv, data);
		else if (!ft_strcmp(argv[0], "pwd"))
			pwd_cmd(data);
		else if (!ft_strcmp(argv[0], "cd"))
			cd_cmd(argv, data);
		else if (!ft_strcmp(argv[0], "env"))
			env_cmd(data);
		else if (!ft_strcmp(argv[0], "unset"))
			unset_cmd(argv, data);
		else if (!ft_strcmp(argv[0], "export"))
			export_cmd(argv, data);
	}
	reset_pipes(old_stdin, old_stdout);
}
