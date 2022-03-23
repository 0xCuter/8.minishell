/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:37:08 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/23 11:11:58 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Searches for the `cmd` path
static char	*find_command(char *cmd, char **path_split)
{
	struct stat	test;
	int			size;
	char		found_command_location;
	char		*cmd_path;

	found_command_location = 0;
	while (found_command_location == 0 && *path_split != NULL)
	{
		size = ft_strlen(*path_split) + ft_strlen(cmd) + 2;
		cmd_path = malloc(size * sizeof(char));
		ft_strlcpy(cmd_path, *path_split, size);
		ft_strlcat(cmd_path, "/", size);
		ft_strlcat(cmd_path, cmd, size);
		if (stat(cmd_path, &test) == 0)
		{
			found_command_location = 1;
			return (cmd_path);
		}
		free(cmd_path);
		++path_split;
	}
	return (NULL);
}

//Searches a match for a buitlin
//Returns 1 if it finds one, else 0
static char	execute_builtin(char **cmd_split)
{
	if (!ft_strcmp(cmd_split[0], "echo"))
	{
		echo_cmd(cmd_split);
		return (1);
	}
	else if (!ft_strcmp(cmd_split[0], "exit"))
	{
		exit_cmd(cmd_split);
		return (1);
	}
	else if (!ft_strcmp(cmd_split[0], "pwd"))
	{
		pwd_cmd();
		return (1);
	}
	return (0);
}

//Executes a command in a child process
//Returns the child PID
static int	execute_cmd(char *cmd, char **cmd_split)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		free(cmd);
		error("FORK");
	}
	if (pid == 0)
	{
		if (execve(cmd, cmd_split, NULL))
			error("EXECVE");
	}
	g_child_pid = pid;
	free(cmd);
	return (pid);
}

//Executes a command or a builtin
void	execute(char *line, char **path_split)
{
	char		*cmd;
	int			pid;
	t_list		*cmd_list;
	t_list		*current_cmd;
	t_command	*cmd_content;

	cmd_list = parse_line(line);
	free(line);
	current_cmd = cmd_list;
	while (current_cmd)
	{
		cmd_content = (t_command *)current_cmd->content;
		if (execute_builtin(cmd_content->cmd_split) == 0)
		{
			cmd = find_command(cmd_content->cmd_split[0], path_split);
			if (cmd)
			{
				pid = execute_cmd(cmd, cmd_content->cmd_split);
				waitpid(pid, NULL, 0);
				g_child_pid = 0;
			}
		}
		current_cmd = current_cmd->next;
	}
	ft_lstclear(&cmd_list, clear_cmd_list);
}
