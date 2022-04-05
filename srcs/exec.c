/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:37:08 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/05 13:32:05 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Frees the commands list
static void	clear_cmd(void *cmd_void)
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
			pipe(pipes[1]);
			cmd->stdout_pipe = pipes[1];
		}
		else
		{
			pipes[0] = malloc(2 * sizeof(int *));
			pipe(pipes[0]);
			cmd->stdout_pipe = pipes[0];
		}
	}
}

//Closes the two pipe ends, frees it and sets it to `NULL`
static void	close_pipe(int *pipe[2])
{
	close((*pipe)[0]);
	close((*pipe)[1]);
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

//Executes the commands or builtins
void	exec_cmd_list(t_list *c_list, t_data *data)
{
	t_list		*cmd_elem;
	t_command	*cmd;
	char		**argv;
	int			*pipes[2];

	pipes[0] = NULL;
	pipes[1] = NULL;
	cmd_elem = c_list;
	while (cmd_elem)
	{
		cmd = cmd_elem->content;
		argv = cmd->argv;
		if (argv)
		{
			close_pipes(cmd->id, pipes, 0);
			init_pipes(cmd, pipes);
			if (is_builtin(argv[0]))
				exec_builtin(cmd_elem, data, argv);
			else
				exec_cmd(cmd_elem, argv, data);
		}
		cmd_elem = cmd_elem->next;
	}
	close_pipes(0, pipes, 1);
	while(wait(NULL) > 0)
		;
	if (c_list)
		ft_lstclear(&c_list, clear_cmd);
}
