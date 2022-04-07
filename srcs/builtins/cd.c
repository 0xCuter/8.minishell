/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:09:02 by scuter            #+#    #+#             */
/*   Updated: 2022/04/07 01:03:07 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pwd(t_data *data, char *pwd, char *str)
{
	char	*join;
	char	*envar;

	if (!pwd)
		return ;
	join = ft_strjoin(str, pwd);
	if (!join)
		error("MALLOC");
	envar = find_key(data, str);
	if (envar)
		replace_env(data, envar, join);
	else
		data->envs = add_line(join, data->envs);
	free(join);
	free(pwd);
}

static void	*add_home(t_data *data, char **argv)
{
	char		*home;
	char		*sub_path;

	if (!ft_strncmp(argv[1], "~/", 2))
	{
		home = get_env(data, "HOME");
		if (home)
		{
			sub_path = ft_substr(argv[1], 1, ft_strlen(argv[1]));
			free(argv[1]);
			argv[1] = ft_strjoin(home, sub_path);
			free(sub_path);
		}
	}
	return (argv[1]);
}

// Change the working directory of the current shell execution environment.
void	cd_cmd(char **argv, t_data *data)
{
	char	*path;
	char	*pwd;

	data->exit_status = 0;
	path = NULL;
	if (!argv[1] || (!ft_strcmp(argv[1], "~")) || (!ft_strcmp(argv[1], "--")))
	{
		path = get_env(data, "HOME");
		if (!path)
		{
			data->exit_status = 1;
			ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
			return ;
		}
	}
	else if (!ft_strcmp(argv[1], "-"))
		path = get_env(data, "OLDPWD");
	else
		path = add_home(data, argv);
	pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		free(pwd);
		data->exit_status = 1;
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return ;
	}
	set_pwd(data, pwd, "OLDPWD=");
	pwd = getcwd(NULL, 0);
	set_pwd(data, pwd, "PWD=");
}
