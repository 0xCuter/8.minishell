/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:35:37 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/09 14:25:33 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_cmd_in_path(char *cmd, t_data *data, char *allocated, struct stat *s)
{
	char	*path_var;
	char	**path_split_start;
	char	**path_split;
	char	*cmd_path;
	int		size;

	path_var = get_env(data, "PATH");
	if (path_var == NULL)
		return (NULL);
	path_split = ft_split(path_var, ':');
	path_split_start = path_split;
	while (path_split && *path_split)
	{
		size = ft_strlen(*path_split) + ft_strlen(cmd) + 2;
		cmd_path = malloc(size * sizeof(char));
		if (cmd_path != NULL)
		{
			ft_strlcpy(cmd_path, *path_split, size);
			ft_strlcat(cmd_path, "/", size);
			ft_strlcat(cmd_path, cmd, size);
			if (stat(cmd_path, s) == 0 && !(s->st_mode & S_IFDIR))
			{
				*allocated = 1;
				free_tab(path_split_start);
				return (cmd_path);
			}
			free(cmd_path);
			cmd_path = NULL;
		}
		++path_split;
	}
	free_tab(path_split_start);
	return (NULL);
}

//Returns 1 if the cmd is an absolute or relative path
// (if it start with / or ./ or ../)
//Else 0
static char	cmd_is_path(char *cmd)
{
	if (cmd[0] != 0
		&& (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/')))
		return (1);
	else if (cmd[0] != 0 && cmd[1] != 0
			&& (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/'))
		return (1);
	return (0);
}

//Searches for the `cmd` path
//Returns the command path if it is not a directory and
// the user has the permission to execute it
//Else returns `NULL`
static char	*find_cmd(char *cmd, t_data *data, char *allocated)
{
	struct stat	s;
	char		*cmd_path;

	if (!ft_strcmp(cmd, data->exec_name))
		globs.last_child = 0;
	*allocated = 0;
	cmd_path = NULL;
	if (cmd_is_path(cmd))
	{
		if (stat(cmd, &s))
		{
			data->exit_status = 127;
			ft_putstr_fd("-minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
			return (NULL);
		}
		else if (s.st_mode & S_IFDIR)
		{
			data->exit_status = 126;
			ft_putstr_fd("-minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putendl_fd(": is a directory", STDERR_FILENO);
			return (NULL);
		}
		else
			cmd_path = cmd;
	}
	else
		cmd_path = find_cmd_in_path(cmd, data, allocated, &s);
	if (cmd_path == NULL)
	{
		data->exit_status = 127;
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	else if (!(s.st_mode & S_IXUSR))
	{
		data->exit_status = 126;
		if (*allocated)
			free(cmd_path);
		cmd_path = NULL;
		ft_putstr_fd("-minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	}
	return (cmd_path);
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

//Redirects stdin or stdout
static void	setup_redirs(t_command *cmd)
{
	if (cmd->redir_stdin)
	{
		if (dup2(*cmd->redir_stdin, STDIN_FILENO) == -1)
			error("DUP2");
		if (close(*cmd->redir_stdin) == -1)
			error("CLOSE");
		free_null((void *)&cmd->redir_stdin);
	}
	if (cmd->redir_stdout)
	{
		if (dup2(*cmd->redir_stdout, STDOUT_FILENO) == -1)
			error("DUP2");
		if (close(*cmd->redir_stdout) == -1)
			error("CLOSE");
		free_null((void *)&cmd->redir_stdout);
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
			error("FORK");
		if (pid == 0)
		{
			setup_pipes(cmd);
			setup_redirs(cmd);
			if (execve(cmd_path, argv, data->envs))
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(cmd_path, STDERR_FILENO);
				free(cmd_path);
				ft_putstr_fd(": cannot execute binary file", STDERR_FILENO);
				error(": ");
			}
		}
		if (cmd_path_allocated)
			free(cmd_path);
	}
	return (pid);
}
