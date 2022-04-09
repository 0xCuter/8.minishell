/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:35:37 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/09 16:24:39 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*find_cmd_in_path(char *c, t_data *d, char *allocd, struct stat *s)
{
	char	*path_var;
	char	**path_split_start;
	char	**path_split;
	char	*cmd_path;
	int		size;

	path_var = get_env(d, "PATH");
	if (path_var == NULL)
		return (NULL);
	path_split = ft_split(path_var, ':');
	path_split_start = path_split;
	while (path_split && *path_split)
	{
		size = ft_strlen(*path_split) + ft_strlen(c) + 2;
		cmd_path = malloc(size * sizeof(char));
		if (cmd_path != NULL)
		{
			ft_strlcpy(cmd_path, *path_split, size);
			ft_strlcat(cmd_path, "/", size);
			ft_strlcat(cmd_path, c, size);
			if (stat(cmd_path, s) == 0 && !(s->st_mode & S_IFDIR))
			{
				*allocd = 1;
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

//Searches for the `cmd` path
//Returns the command path if it is not a directory and
// the user has the permission to execute it
//Else returns `NULL`
static char	*find_cmd(char *cmd, t_data *data, char *allocated)
{
	struct stat	s;
	char		*cmd_path;

	if (!ft_strcmp(cmd, data->exec_name))
		g_globs.last_child = 0;
	*allocated = 0;
	cmd_path = NULL;
	if (cmd_is_path(cmd))
	{
		if (stat(cmd, &s))
			return (error_ret_null(data, 127, "-minishell: ",
					ft_strjoin(cmd, ": No such file or directory")));
		else if (s.st_mode & S_IFDIR)
			return (error_ret_null(data, 126, "-minishell: ",
					ft_strjoin(cmd, ": is a directory")));
		else
			cmd_path = cmd;
	}
	else
		cmd_path = find_cmd_in_path(cmd, data, allocated, &s);
	if (cmd_path == NULL)
		return (error_ret_null(data, 127, NULL,
				ft_strjoin(cmd, ": command not found")));
	else if (!(s.st_mode & S_IXUSR))
	{
		if (*allocated)
			free(cmd_path);
		return (error_ret_null(data, 126, "-minishell: ",
				ft_strjoin(cmd, ": Permission denied")));
	}
	return (cmd_path);
}

static void	child_process_error(char *cmd_path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_path, STDERR_FILENO);
	free(cmd_path);
	ft_putstr_fd(": cannot execute binary file", STDERR_FILENO);
	error(": ");
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
			setup_redirs(cmd, NULL, NULL);
			if (execve(cmd_path, argv, data->envs))
				child_process_error(cmd_path);
		}
		if (cmd_path_allocated)
			free(cmd_path);
	}
	return (pid);
}
