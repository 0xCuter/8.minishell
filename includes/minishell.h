/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:08:58 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/05 01:17:30 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
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

// # define PROMPT "Minishell$ "
# define WAIT_PROMPT "> "
# define METACHARS " \t\n\v\f\r|<>\"'"
# define METACHARS_DOLLAR_SIGN " \t\n\v\f\r|<>\"'$"
# define METACHARS_QUOTES "\"'"
# define METACHARS_NO_QUOTES " \t\n\v\f\r|<>"
# define METACHARS_WHITE_SPACES " \t\n\v\f\r"
# define METACHARS_NO_WHITE_SPACES "|<>\"'"

typedef struct s_command {
	int		id;
	char	**argv;
	char	stdin_piped;
	char	stdout_piped;
	int		*stdin_pipe;
	int		*stdout_pipe;
	int		*redir_stdin;
	int		*redir_stdout;
}	t_command;

typedef struct s_data {
	char	**envs;
	char	**path_split;
	char	*line;
}	t_data;

//utils.c
void	error(const char *error);
void	free_null(void **elem);
char	in_quotes(const char *s, char *r);

//str_utils.c
char	*ft_str_replace(char *s, int start, int end, char *fit);
char	*ft_str_chrset_ign_quotes(const char *s, const char *set);
char	*ft_str_chrset(const char *s, const char *set);
char	*ft_str_chrset_rev(const char *s, const char *set);
char	*mod_strjoin(char *s1, char *s2);

//tab_utils.c
char	**duplicate_tab(char **tab);
void	sort_tab(char **tab);
char	**add_line(char *line, char **tab);
char	**remove_line(char *line, char **tab);
void	free_tab(char **tab);

//env_utils.c
char	*find_envar(t_data *data, char *var_name);
char	*find_key(t_data *data, char *str);
char	*get_env(t_data *data, char *key);
void	replace_env(t_data *data, char *envar, char *line);

//init.c
void	init_envs(t_data *data, char **envp);
void	init_path_split(t_data *data);

//main.c
void	prompt(t_data *data, int exit_flag);

//signals.c
void	setup_signals(void);

//replace_input.c
char	*replace_vars(char *s, t_data *data);
void	replace_quotes(char **s, t_data *data, int *pos);

//init_cmds.c
t_list	*init_cmds(char *line, t_data *data, char *syntax_error);

//init_redirections.c
char	init_pipe(t_command *cmd, char *stdout_pipe, char **cur_char);
void	init_heredoc(t_command *cmd, char **current_token);
void	init_append(t_command *cmd, char **current_token);
void	init_redir_stdin(t_command *cmd, char **current_token);
void	init_redir_stdout(t_command *cmd, char **current_token);

//exec.c
void	execute(t_data *data, char *line);
void	exec_cmd_list(t_list *cmds, t_data *data);

//exec_builtin.c
char	is_builtin(char *cmd_name);
void	exec_builtin(t_list *cmd_elem, t_data *data, char **argv);

//exec_cmd.c
void	exec_cmd(t_list *cmd_elem, char **argv, t_data *data);

//syntax.c
char	*check_syntax(char *line);
char	*get_meta_arg(char *meta, int *meta_sub_size);

//---BUILTINS
//echo.c
void	echo_cmd(char **argv);

//exit.c
void	exit_cmd(char **argv);

//pwd.c
void	pwd_cmd(void);

//cd.c
void	cd_cmd(char **argv, t_data *data);

//env.c
void	env_cmd(t_data *data);

//unset.c
void	unset_cmd(char **argv, t_data *data);

//export.c
void	export_cmd(char **argv, t_data *data);

#endif
