/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:08:58 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/24 17:11:32 by vvandenb         ###   ########.fr       */
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

extern int	g_child_pid;

extern char **environ;

//utils.c
void	error(const char *error);

//signals.c
void	setup_signals();

//parser.c
t_list	*parse_line(char *line);

//command.c
void	execute(char *line, char **path_split);

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
void	env_cmd(void);

#endif
