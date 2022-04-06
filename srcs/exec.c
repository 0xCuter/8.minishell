/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:37:08 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/06 16:31:26 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//Assigns one of two pipes to the command
static void	init_pipes(t_command *cmd, int *pipes[2])
{
	if (cmd->stdin_piped)
	{
		if (cmd->id % 2)
			cmd->stdin_pipe = pipes[0];
		else
			cmd->stdin_pipe = pipes[1];
	}
	if (cmd->stdout_piped)
	{
		if (cmd->id % 2)
		{
			pipes[1] = malloc(2 * sizeof(int *));
			if (pipe(pipes[1]) == -1)
				error("PIPE");
			cmd->stdout_pipe = pipes[1];
		}
		else
		{
			pipes[0] = malloc(2 * sizeof(int *));
			if (pipe(pipes[0]) == -1)
				error("PIPE");
			cmd->stdout_pipe = pipes[0];
		}
	}
}

//Closes the two pipe ends, frees it and sets it to `NULL`
static void	close_pipe(int *pipe[2])
{
	if (close((*pipe)[0]) == -1)
		error("CLOSE");
	if (close((*pipe)[1]) == -1)
		error("CLOSE");
	free_null((void*)pipe);
}

//If `end`, closes all open pipes
//Else, closes the left most pipe currently open
static void	close_pipes(int cmd_id, int *pipes[2], char end)
{
	if (end)
	{
		if (pipes[0])
			close_pipe(&pipes[0]);
		if (pipes[1])
			close_pipe(&pipes[1]);
		return ;
	}
	if (cmd_id < 2)
		return ;
	if (cmd_id % 2)
		close_pipe(&pipes[1]);
	else
		close_pipe(&pipes[0]);
}

//Waits for all children
//If `last_pid != -1`, saves the last one's exit status to `data`
static void	wait_children(t_data *data, int last_pid)
{
	int	waited_pid;
	int	waited_status;

	waited_pid = wait(&waited_status);
	if (last_pid != -1 && waited_pid == last_pid)
		data->exit_status = WEXITSTATUS(waited_status);
	while(waited_pid > 0)
	{
		waited_pid = wait(&waited_status);
		if (last_pid != -1 && waited_pid == last_pid)
			data->exit_status = WEXITSTATUS(waited_status);
	}
}

//Executes a command or a builtin
static int	exec_cmd_elem(t_command *cmd, t_data *data, int *pipes[2])
{
	char	**argv;
	int		pid;

	pid = -1;
	argv = cmd->argv;
	if (argv)
	{
		close_pipes(cmd->id, pipes, 0);
		init_pipes(cmd, pipes);
		if (is_builtin(argv[0]))
		{
			pid = -1;
			exec_builtin(cmd, data, argv);
		}
		else if (cmd->error_init == 0)
			pid = exec_cmd(cmd, argv, data);
	}
	return (pid);
}

//Executes the commands or builtins
void	exec_cmd_list(t_list *c_list, t_data *data)
{
	int		*pipes[2];
	int		last_pid;
	t_list	*cmd_elem;

	ft_memset(pipes, 0, 2 * sizeof(int *));
	last_pid = -1;
	cmd_elem = c_list;
	while (cmd_elem)
	{
		last_pid = exec_cmd_elem(cmd_elem->content, data, pipes);
		cmd_elem = cmd_elem->next;
	}
	close_pipes(0, pipes, 1);
	wait_children(data, last_pid);
	if (c_list)
		ft_lstclear(&c_list, clear_cmd);
}
