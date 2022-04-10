/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 14:40:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/10 15:22:09 by vvandenb         ###   ########.fr       */
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

//Kills all children and waits for them
void	kill_children(void)
{
	pid_t	*temp;
	int		waited_pid;
	int		i;

	i = 0;
	while (g_globs.pids && g_globs.pids[i])
	{
		kill(g_globs.pids[i], SIGKILL);
		++i;
	}
	waited_pid = wait(NULL);
	while (waited_pid > 0)
		waited_pid = wait(NULL);
	temp = g_globs.pids;
	g_globs.pids = NULL;
	free(temp);
}

//Waits for all children
//If `last_pid != -1`, saves the last one's exit status to `data`
void	wait_children(t_data *data, int last_pid)
{
	int		waited_pid;
	int		waited_status;
	pid_t	*temp;

	waited_pid = wait(&waited_status);
	if (last_pid != NO_PID && last_pid != FORK_ERROR && waited_pid == last_pid)
	{
		data->exit_status = WEXITSTATUS(waited_status);
		if (WIFSIGNALED(waited_status))
			data->exit_status = 128 + WTERMSIG(waited_status);
	}
	while (waited_pid > 0)
	{
		waited_pid = wait(&waited_status);
		if (last_pid != NO_PID && last_pid != FORK_ERROR
			&& waited_pid == last_pid)
		{
			data->exit_status = WEXITSTATUS(waited_status);
			if (WIFSIGNALED(waited_status))
				data->exit_status = 128 + WTERMSIG(waited_status);
		}
	}
	temp = g_globs.pids;
	g_globs.pids = NULL;
	free(temp);
}

//Frees a command structure
void	clear_cmd(void *cmd_void)
{
	t_command	*cmd;

	cmd = (t_command *)cmd_void;
	if (cmd->redir_stdin)
	{
		close(cmd->redir_stdin[0]);
		free(cmd->redir_stdin);
	}
	if (cmd->redir_stdout)
	{
		close(*cmd->redir_stdout);
		free(cmd->redir_stdout);
	}
	if (cmd->argv)
		free_tab(cmd->argv);
	free(cmd);
}
