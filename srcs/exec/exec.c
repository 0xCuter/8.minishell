/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:37:08 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/10 09:00:58 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free_null((void *)pipe);
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

//Executes a command or a builtin
static pid_t	exec_cmd_elem(t_command *cmd, t_data *data, int *pipes[2])
{
	char	**argv;
	pid_t	pid;

	pid = -1;
	argv = cmd->argv;
	if (argv)
	{
		close_pipes(cmd->id, pipes, 0);
		init_pipes(cmd, pipes);
		if (cmd->error_init == 0)
		{
			if (is_builtin(argv[0]))
			{
				pid = -1;
				exec_builtin(cmd, data, argv);
			}
			else
				pid = exec_cmd(cmd, argv, data);
		}
		else
			data->exit_status = 1;
	}
	return (pid);
}

//Executes the commands or builtins
void	exec_cmd_list(t_list *c_list, t_data *data)
{
	int		*pipes[2];
	pid_t	pid;
	t_list	*cmd_elem;

	ft_memset(pipes, 0, 2 * sizeof(int *));
	pid = -1;
	cmd_elem = c_list;
	while (cmd_elem)
	{
		pid = exec_cmd_elem(cmd_elem->content, data, pipes);
		if (pid != -1)
			add_g_pids(pid);
		cmd_elem = cmd_elem->next;
	}
	close_pipes(0, pipes, 1);
	wait_children(data, pid);
	g_globs.last_child = 1;
	if (c_list)
		ft_lstclear(&c_list, clear_cmd);
}
