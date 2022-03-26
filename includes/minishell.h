/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:08:58 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/26 16:05:50 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>

# include "libft.h"

# define PROMPT "Minishell$ "

typedef struct s_command {
	char	**cmd_split;
}	t_command;

typedef struct s_data {
	char	**envs;
	// char	**envs_export;
	char	**path_split;
	char	*line;
}	t_data;

extern int	g_child_pid;

//utils.c
void	error(const char *error);
void	free_tab(char **tab);
char	*ft_str_replace(char *s, int start, int end, char *fit);

//init.c
void	init_envs(t_data *data, char **envp);
// void	init_envs_export(t_data *data);
void	init_path_split(t_data *data);

//signals.c
void	setup_signals(void);

//parser.c
t_list	*parse_line(char *line);

//command.c
void	execute(t_data *data, char *line);

//syntax.c
char	*check_syntax(char *line, t_data *data);

//---BUILTINS
//echo.c
void	echo_cmd(char **argv);

//exit.c
void	exit_cmd(char **argv);

//pwd.c
int		pwd_cmd(void);

//cd.c
void	cd_cmd(char **argv);

//env.c
void	env_cmd(t_data *data);

//unset.c
void	unset_cmd(char **argv, t_data *data);

//var.c
char	*find_envar(t_data *data, char *var_name);

#endif
