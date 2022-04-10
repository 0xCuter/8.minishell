/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:35:37 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/10 15:22:34 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Inits the global PIDs list or adds a PID to it
void	add_g_pids(pid_t pid)
{
	pid_t	*temp;
	pid_t	*temp_bis;
	int		i;

	if (g_globs.pids == NULL)
	{
		g_globs.pids = ft_calloc(2, sizeof(pid_t));
		g_globs.pids[0] = pid;
	}
	else
	{
		i = 0;
		while (g_globs.pids[i])
			++i;
		temp = ft_calloc(i + 2, sizeof(pid_t));
		temp[i--] = pid;
		while (i >= 0)
		{
			temp[i] = g_globs.pids[i];
			--i;
		}
		temp_bis = g_globs.pids;
		g_globs.pids = temp;
		free(temp_bis);
	}
}

static void	child_process_error(char *cmd_path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_path, STDERR_FILENO);
	free(cmd_path);
	ft_putstr_fd(": cannot execute binary file", STDERR_FILENO);
	error(": ");
}

//Sets the pipes if needed
static void	setup_pipes(t_command *cmd)
{
	if (cmd->stdin_piped)
	{
		if (dup2(cmd->stdin_pipe[0], STDIN_FILENO) == -1)
			error("DUP2");
		if (close(cmd->stdin_pipe[0]) == -1)
			error("CLOSE");
		if (close(cmd->stdin_pipe[1]) == -1)
			error("CLOSE");
	}
	if (cmd->stdout_piped)
	{
		if (dup2(cmd->stdout_pipe[1], STDOUT_FILENO) == -1)
			error("DUP2");
		if (close(cmd->stdout_pipe[0]) == -1)
			error("CLOSE");
		if (close(cmd->stdout_pipe[1]) == -1)
			error("CLOSE");
	}
}

//Executes a command in a child process
//Returns the child PID
pid_t	exec_cmd(t_command *cmd, char **argv, t_data *data)
{
	pid_t	pid;
	char	cmd_path_allocated;
	char	*cmd_path;

	pid = -1;
	cmd_path = find_cmd(argv[0], data, &cmd_path_allocated);
	if (cmd_path)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("minishell: fork");
			pid = FORK_ERROR;
		}
		else if (pid == 0)
		{
			setup_pipes(cmd);
			setup_redirs(cmd, NULL, NULL);
			if (execve(cmd_path, argv, data->envs))
				child_process_error(cmd_path);
		}
		if (cmd_path_allocated)
			free(cmd_path);
	}
	return (pid);
}
