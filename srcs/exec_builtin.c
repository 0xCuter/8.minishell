/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:35:45 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/30 09:47:38 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Sets the correct pipes
static void	setup_pipes(t_command *cmd, int *old_stdin, int *old_stdout)
{
	if (cmd->read_pipe)
	{
		*old_stdin = dup(STDIN_FILENO);
		dup2(cmd->read_pipe[0], STDIN_FILENO);
		close(cmd->read_pipe[0]);
		free_null((void **)&cmd->read_pipe);
	}
	if (cmd->write_pipe)
	{
		*old_stdout = dup(STDOUT_FILENO);
		dup2(cmd->write_pipe[1], STDOUT_FILENO);
		close(cmd->write_pipe[1]);
	}
}

//Resets stdin/stdout
static void	reset_pipes(int old_stdin, int old_stdout)
{
	if (old_stdin != -2)
	{
		dup2(old_stdin, STDIN_FILENO);
		close(old_stdin);
	}
	if (old_stdout != -2)
	{
		dup2(old_stdout, STDOUT_FILENO);
		close(old_stdout);
	}
}

//Returns 1 if `cmd_name` is a builtin, else 0
char	is_builtin(char *cmd_name)
{
	if (ft_strnstr(BUILTINS, cmd_name, ft_strlen(BUILTINS)))
		return (1);
	return (0);
}

static void	init_redirs(t_command *cmd, int *old_stdin, int *old_stdout)
{
	if (cmd->redir_stdin)
	{
		*old_stdin = dup(STDIN_FILENO);
		dup2(cmd->redir_stdin[0], STDIN_FILENO);
		close(cmd->redir_stdin[0]);
		free_null((void **)&cmd->redir_stdin);
	}
	if (cmd->redir_stdout)
	{
		*old_stdout = dup(STDOUT_FILENO);
		dup2(*cmd->redir_stdout, STDOUT_FILENO);
		close(*cmd->redir_stdout);
		free_null((void **)&cmd->redir_stdin);
	}
}

//Executes a builtin
void	exec_builtin(t_list *cmd_elem, t_data *data, char **argv)
{
	int	old_stdin = -2;
	int	old_stdout = -2;

	setup_pipes(cmd_elem->content, &old_stdin, &old_stdout);
	init_redirs(cmd_elem->content, &old_stdin, &old_stdout);
	if (argv)
	{
		if (!ft_strcmp(argv[0], "echo"))
			echo_cmd(argv);
		else if (!ft_strcmp(argv[0], "exit"))
			exit_cmd(argv);
		else if (!ft_strcmp(argv[0], "pwd"))
			pwd_cmd();
		else if (!ft_strcmp(argv[0], "cd"))
			cd_cmd(argv);
		else if (!ft_strcmp(argv[0], "env"))
			env_cmd(data);
		else if (!ft_strcmp(argv[0], "unset"))
			unset_cmd(argv, data);
		else if (!ft_strcmp(argv[0], "export"))
			export_cmd(argv, data);
	}
	reset_pipes(old_stdin, old_stdout);
}
