/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:08:58 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/23 00:18:24 by scuter           ###   ########.fr       */
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

int CHILD_PID;

//utils.c
void	error(const char *error);

//signals.c
char		setup_signals();

//command.c
char	*find_command(char *line, char **path_split);
int		execute(char *command);


//echo.c
void	echo_cmd(char **argv);

//exit.c
void	exit_cmd(char **argv);

//pwd.c
int		pwd_cmd(void);

#endif
