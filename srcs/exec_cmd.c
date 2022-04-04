/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:35:37 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/04 16:46:37 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Searches for the `cmd` path
//Returns the command path if it is not a directory and
// the user has the permission to execute it
//Else returns `NULL`
static char	*find_command(char *cmd, char **path_split, char *allocated)
{
	struct stat	s;
	int			size;
	char		*cmd_path;

	*allocated = 0;
	cmd_path = NULL;
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (stat(cmd, &s) == 0 && !(s.st_mode & S_IFDIR))
			cmd_path = cmd;
	}
	else
	{
		while (*path_split != NULL)
		{
			size = ft_strlen(*path_split) + ft_strlen(cmd) + 2;
			cmd_path = malloc(size * sizeof(char));
			ft_strlcpy(cmd_path, *path_split, size);
			ft_strlcat(cmd_path, "/", size);
			ft_strlcat(cmd_path, cmd, size);
			if (stat(cmd_path, &s) == 0 && !(s.st_mode & S_IFDIR))
			{
				*allocated = 1;
				break ;
			}
			free(cmd_path);
			cmd_path = NULL;
			++path_split;
		}
	}
	if (cmd_path == NULL)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	else if (!(s.st_mode & S_IXUSR))
	{
		if (*allocated)
			free(cmd_path);
		cmd_path = NULL;
		ft_putstr_fd("-minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	return (cmd_path);
}

//Sets the pipes if needed
static void	setup_pipes(t_command *cmd)
{
	if (cmd->stdin_piped)
	{
		dup2(cmd->stdin_pipe[0], STDIN_FILENO);
		close(cmd->stdin_pipe[0]);
		close(cmd->stdin_pipe[1]);
	}
	if (cmd->stdout_piped)
	{
		dup2(cmd->stdout_pipe[1], STDOUT_FILENO);
		close(cmd->stdout_pipe[0]);
		close(cmd->stdout_pipe[1]);
	}
}

//Redirects stdin or stdout
static void	setup_redirs(t_command *cmd)
{
	if (cmd->redir_stdin)
	{
		dup2(cmd->redir_stdin[0], STDIN_FILENO);
		close(cmd->redir_stdin[0]);
		free_null((void **)&cmd->redir_stdin);
	}
	if (cmd->redir_stdout)
	{
		dup2(*cmd->redir_stdout, STDOUT_FILENO);
		close(*cmd->redir_stdout);
		free_null((void **)&cmd->redir_stdout);
	}
}

//Executes a command in a child process
//Returns the child PID
void	exec_cmd(t_list *cmd_elem, char **argv, t_data *data)
{
	int		pid;
	char	cmd_allocated;
	char	*cmd;

	cmd = find_command(argv[0], data->path_split, &cmd_allocated);
	if (cmd)
	{
		pid = fork();
		if (pid == -1)
			error("FORK");
		if (pid == 0)
		{
			setup_pipes(cmd_elem->content);
			setup_redirs(cmd_elem->content);
			if (execve(cmd, argv, data->envs))
				error("EXECVE");
		}
		if (cmd_allocated)
			free(cmd);
	}
}
