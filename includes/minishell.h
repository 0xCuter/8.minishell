/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:08:58 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/23 11:14:17 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <signal.h>

# include "libft.h"

# define PROMPT "Minishell$ "

typedef struct s_command {
	char	**cmd_split;
}	t_command;

int	g_child_pid;

//utils.c
void	error(const char *error);
void	clear_cmd_list(void *cmd_void);

//signals.c
char	setup_signals(void);

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

#endif
