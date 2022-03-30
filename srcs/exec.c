/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:37:08 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/30 15:50:43 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Frees the commands list
static void	clear_cmd(void *cmd_void)
{
	t_command	*cmd;

	cmd = (t_command *)cmd_void;
	if (cmd->read_pipe)
	{
		close(cmd->read_pipe[0]);
		close(cmd->read_pipe[1]);
		free(cmd->read_pipe);
	}
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

//Executes the commands or builtins
void	exec_cmd_list(t_list *c_list, t_data *data)
{
	t_list	*cmd_elem;
	char	**argv;

	cmd_elem = c_list;
	while (cmd_elem)
	{
		argv = ((t_command *)cmd_elem->content)->argv;
		if (is_builtin(argv[0]))
			exec_builtin(cmd_elem, data, argv);
		else
			exec_cmd(cmd_elem, data->path_split, argv, data);
		cmd_elem = cmd_elem->next;
	}
	if (c_list)
		ft_lstclear(&c_list, clear_cmd);
}
