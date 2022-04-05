/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:09:02 by scuter            #+#    #+#             */
/*   Updated: 2022/04/05 02:57:05 by scuter           ###   ########.fr       */
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
		add_line(join, data->envs);
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

	path = NULL;
	if (argv && argv[1] && argv[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return ;
	}
	if (!argv[1] || (!ft_strcmp(argv[1], "~")) || (!ft_strcmp(argv[1], "--")))
	{
		path = get_env(data, "HOME");
		if (!path)
		{
			ft_putendl_fd("cd: HOME not set", 2);
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
		ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	set_pwd(data, pwd, "OLDPWD=");
	pwd = getcwd(NULL, 0);
	set_pwd(data, pwd, "PWD=");
}
