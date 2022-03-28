/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:37:08 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/28 18:35:22 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Searches for the `cmd` path
static char	*find_command(char *cmd, char **path_split, char *allocated)
{
	struct stat	test;
	int			size;
	char		*cmd_path;

	*allocated = 0;
	if (stat(cmd, &test) == 0)
		return (cmd);
	while (*path_split != NULL)
	{
		size = ft_strlen(*path_split) + ft_strlen(cmd) + 2;
		cmd_path = malloc(size * sizeof(char));
		ft_strlcpy(cmd_path, *path_split, size);
		ft_strlcat(cmd_path, "/", size);
		ft_strlcat(cmd_path, cmd, size);
		if (stat(cmd_path, &test) == 0)
		{
			*allocated = 1;
			return (cmd_path);
		}
		free(cmd_path);
		++path_split;
	}
	return (NULL);
}

static void	setup_pipes(t_command *cmd)
{
	static int	call_count = 0;
	static int	old_stdin = 0;
	static int	old_stdout = 0;

	if (call_count == 0)
	{
		if (cmd->read_pipe)
		{
			old_stdin = dup(STDIN_FILENO);
			// printf("CMD %i reading fd %i\n", cmd->id, cmd->read_pipe[0]);
			dup2(cmd->read_pipe[0], STDIN_FILENO);
			close(cmd->read_pipe[0]);
		}
		else if (cmd->write_pipe)
		{
			old_stdout = dup(STDOUT_FILENO);
			// printf("CMD %i writing fd %i\n", cmd->id, cmd->write_pipe[1]);
			dup2(cmd->write_pipe[1], STDOUT_FILENO);
			close(cmd->write_pipe[1]);
		}
		call_count = 1;
	}
	else
	{
		if (old_stdin)
		{
			dup2(old_stdin, STDIN_FILENO);
			close(old_stdin);
			old_stdin = 0;
		}
		if (old_stdout)
		{
			dup2(old_stdout, STDOUT_FILENO);
			close(old_stdout);
			old_stdout = 0;
		}
		call_count = 0;
	}
}

//Returns 1 if `cmd_name` is a builtin, else 0
static char	is_builtin(char *cmd_name)
{
	if (ft_strnstr(BUILTINS, cmd_name, ft_strlen(BUILTINS)))
		return (1);
	return (0);
}

//Executes a builtin
static void	execute_builtin(t_list *cmd_elem, t_data *data, char **argv)
{
	setup_pipes(cmd_elem->content);
	// init_redirections(cmd_elem);
	if (argv)
	{
		if (!ft_strcmp(argv[0], "echo"))
			echo_cmd(argv);
		else if (!ft_strcmp(argv[0], "exit"))
			exit_cmd(argv);
		else if (!ft_strcmp(argv[0], "pwd"))
			pwd_cmd();
		else if (!ft_strcmp(argv[0], "cd"))
			cd_cmd(argv);
		else if (!ft_strcmp(argv[0], "env"))
			env_cmd(data);
		else if (!ft_strcmp(argv[0], "unset"))
			unset_cmd(argv, data);
	}
	setup_pipes(cmd_elem->content);
}

//Frees the commands list
static void	clear_cmd(void *cmd_void)
{
	t_command	*cmd;

	cmd = (t_command *)cmd_void;
	if (cmd->read_pipe)
		free(cmd->read_pipe);
	if (cmd->args)
		free(cmd->args);
	free(cmd);
}

//Executes a command in a child process
//Returns the child PID
static void	execute_cmd(t_list *cmd_elem, char **path_split, char **argv)
{
	int		pid;
	char	cmd_allocated;
	char	*cmd;

	setup_pipes(cmd_elem->content);
	cmd = find_command(argv[0], path_split, &cmd_allocated);
	if (cmd)
	{
		pid = fork();
		if (pid == -1)
			error("FORK");
		if (pid == 0)
		{
			if (execve(cmd, argv, NULL))
				error("EXECVE");
		}
		g_child_pid = pid;
		waitpid(pid, NULL, 0);
		if (cmd_allocated)
			free(cmd);
		g_child_pid = 0;
	}
	setup_pipes(cmd_elem->content);
}

//Executes the commands or builtins
void	execute_cmd_list(t_list *c_list, t_data *data)
{
	t_list	*cmd_elem;
	char	**argv;

	cmd_elem = c_list;
	while (cmd_elem)
	{
		argv = ft_split(((t_command *)cmd_elem->content)->args, ' ');
		if (is_builtin(argv[0]))
			execute_builtin(cmd_elem, data, argv);
		else
			execute_cmd(cmd_elem, data->path_split, argv);
		ft_free_split(argv);
		cmd_elem = cmd_elem->next;
	}
	if (c_list)
		ft_lstclear(&c_list, clear_cmd);
}
