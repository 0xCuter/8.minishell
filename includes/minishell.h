/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:08:58 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/01 09:07:44 by vvandenb         ###   ########.fr       */
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

# define PROMPT "Minishell$ "
# define WAIT_PROMPT "> "
# define METACHARS " \t\n\v\f\r|<>\"'"
# define METACHARS_DOLLAR_SIGN " \t\n\v\f\r|<>\"'$"
# define METACHARS_NO_QUOTES " \t\n\v\f\r|<>"
# define METACHARS_WHITE_SPACES " \t\n\v\f\r"
# define METACHARS_NO_WHITE_SPACES "|<>\"'"

typedef struct s_command {
	char	**argv;
	int		*read_pipe;
	int		*write_pipe;
	int		*redir_stdin;
	int		*redir_stdout;
}	t_command;

typedef struct s_data {
	char	**envs;
	char	**path_split;
	char	*line;
}	t_data;

extern int	g_child_pid;

//utils.c
void	error(const char *error);
char	*ft_str_replace(char *s, int start, int end, char *fit);
char	*ft_str_chrset(const char *line, const char *set);
char	*ft_str_chrset_rev(const char *line, const char *set);
void	free_null(void **elem);

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

//init.c
void	init_envs(t_data *data, char **envp);
void	init_path_split(t_data *data);

//signals.c
void	setup_signals(void);

//parser.c
t_list	*parse_line(char *line);

//quotes.c
char	*replace_var(char *s, t_data *data, int *i, int *j);
void	replace_quotes(char **s, t_data *data, int *pos, int *j);

//tokenize.c
t_list	*tokenize(char *line, t_data *data, char *syntax_error);

//init_redirections.c
void	init_pipe(t_command *cmd, char **current_token, int **last_pipe);
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
# define BUILTINS "echo exit pwd cd env unset export"
//echo.c
void	echo_cmd(char **argv);

//exit.c
void	exit_cmd(char **argv);

//pwd.c
int		pwd_cmd(void);

//cd.c
void	cd_cmd(char **argv, t_data *data);

//env.c
void	env_cmd(t_data *data);

//unset.c
void	unset_cmd(char **argv, t_data *data);

//export.c
void	export_cmd(char **argv, t_data *data);

#endif
