/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 08:20:11 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/10 15:35:18 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char
	create_cmd_path(char **cmd_path, char *cmd, char *path, struct stat *s)
{
	int	size;

	size = ft_strlen(path) + ft_strlen(cmd) + 2;
	*cmd_path = malloc(size * sizeof(char));
	if (*cmd_path != NULL)
	{
		ft_strlcpy(*cmd_path, path, size);
		ft_strlcat(*cmd_path, "/", size);
		ft_strlcat(*cmd_path, cmd, size);
		if (stat(*cmd_path, s) == 0 && !(s->st_mode & S_IFDIR))
			return (1);
		free(*cmd_path);
	}
	return (0);
}

static char	*find_cmd_in_path(char *c, t_data *d, char *allocd, struct stat *s)
{
	char	*path_var;
	char	**path_split_start;
	char	**path_split;
	char	*cmd_path;

	path_var = get_env(d, "PATH");
	if (path_var == NULL)
		return (NULL);
	path_split = ft_split(path_var, ':');
	if (path_split == NULL)
		return (NULL);
	path_split_start = path_split;
	cmd_path = NULL;
	while (*path_split)
	{
		if (create_cmd_path(&cmd_path, c, *path_split, s))
		{
			*allocd = 1;
			free_tab(path_split_start);
			return (cmd_path);
		}
		++path_split;
	}
	free_tab(path_split_start);
	return (NULL);
}

static char	*cmd_is_path_check(char *cmd, t_data *data, struct stat *s)
{
	if (stat(cmd, s))
		return (error_ret_null(data, 127, "-minishell: ",
				ft_strjoin(cmd, ": No such file or directory")));
	else if (s->st_mode & S_IFDIR)
		return (error_ret_null(data, 126, "-minishell: ",
				ft_strjoin(cmd, ": is a directory")));
	else
		return (cmd);
}

//Searches for the `cmd` path
//Returns the command path only if it is accessible
//Else returns `NULL`
char	*find_cmd(char *cmd, t_data *data, char *allocated)
{
	struct stat	s;
	char		*cmd_path;

	if (!ft_strcmp(cmd, data->exec_name))
		g_globs.last_child = 0;
	*allocated = 0;
	if (cmd_is_path(cmd))
		cmd_path = cmd_is_path_check(cmd, data, &s);
	else
	{
		cmd_path = find_cmd_in_path(cmd, data, allocated, &s);
		if (cmd_path == NULL)
			return (error_ret_null(data, 127, NULL,
					ft_strjoin(cmd, ": command not found")));
	}
	if (cmd_path != NULL && !(s.st_mode & S_IXUSR))
	{
		if (*allocated)
			free(cmd_path);
		return (error_ret_null(data, 126, "-minishell: ",
				ft_strjoin(cmd, ": Permission denied")));
	}
	return (cmd_path);
}
