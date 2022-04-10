/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:08:58 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/10 15:22:32 by vvandenb         ###   ########.fr       */
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

# include "libft.h"

# define DEFAULT_PATH "PATH=/usr/local/bin:/usr/local/sbin:\
/usr/bin:/usr/sbin:/bin:/sbin:."
# define DEFAULT_PROMPT "Minishell$ "
# define PROMPT_HEAD "\001\e[1;33m\002@42\001\e[1;32m\002Nice\001\e[0m\002:\001\e[1;36m\002"
# define WAIT_PROMPT "> "
# define VAR_CHARS " \t\n\v\f\r|<>\"'?$="
# define METACHARS " \t\n\v\f\r|<>\"'"
# define METACHARS_DOLLAR_SIGN " \t\n\v\f\r|<>\"'$"
# define METACHARS_QUOTES "\"'"
# define METACHARS_NO_QUOTES " \t\n\v\f\r|<>"
# define METACHARS_WHITE_SPACES " \t\n\v\f\r"
# define METACHARS_NO_WHITE_SPACES "|<>\"'"

# define NO_PID -1
# define FORK_ERROR -2

typedef struct s_command {
	int		id;
	char	error_init;
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
	char	*line;
	char	*exec_name;
	int		exit_status;
	int		cmd_count;
}	t_data;

typedef struct s_globs {
	pid_t	*pids;
	char	last_child;
	char	heredoc_killed;
}	t_globs;

extern t_globs	g_globs;

//prompt.c
char	*prompt(t_data *data);
char	trailing_pipeline(char **line, t_data *data);

//signals.c
void	setup_signals(void);
void	signal_handler(int sig);
void	heredoc_signal(void);

//syntax.c
char	check_syntax(char *line, t_data *data);

//parse.c
char	*get_meta_arg(char *meta, int *meta_sub_size, t_data *data);

//replace_input.c
char	*replace_vars(char *s, t_data *data);
void	replace_quotes(char **s, t_data *data, int *pos);

//init.c
void	init_envs(t_data *data, char **envp);
void	init_path_split(t_data *data);

//init_cmds.c
t_list	*init_cmds(char *line, t_data *data);

//init_redirs.c
char	init_heredoc(t_command *cmd, char **cur, t_data *data);
char	init_append(t_command *cmd, char **cur, t_data *data);
char	init_redir_stdin(t_command *cmd, char **cur, t_data *data);
char	init_redir_stdout(t_command *cmd, char **cur, t_data *data);
//init_cmds_bis.c
char	init_pipe(t_command *cmd, char *stdout_pipe, char **cur_char);
void	add_argv(t_command *cmd, char **cur_char, t_data *data);

//utils/
// utils.c
void	exit_shell(int status, char ctrl_d);
void	error(const char *error);
void	free_null(void **elem);
char	in_quotes(const char *s, char *r);
char	err_ret_1(t_data *data, int error);
// str_utils.c
char	*ft_str_replace(char *s, int start, int end, char *fit);
char	*ft_str_chrset_ign_quotes(const char *s, const char *set);
char	*ft_str_chrset(const char *s, const char *set);
char	*ft_str_chrset_rev(const char *s, const char *set);
char	*mod_strjoin(char *s1, char *s2);
// tab_utils.c
char	**duplicate_tab(char **tab);
void	sort_tab(char **tab);
char	**add_line(char *line, char **tab);
char	**remove_line(char *line, char **tab);
void	free_tab(char **tab);
// env_utils.c
char	*find_envar(t_data *data, char *var_name);
char	*find_key(t_data *data, char *str);
char	*get_env(t_data *data, char *key);
void	replace_env(t_data *data, char *envar, char *line);
// init_redirs_utils.c
void	error_open(int **fd, char *arg, char *r);
void	close_free(int *fd);
char	free_ret(char *arg, char r);

//execs/
// exec.c
void	execute(t_data *data, char *line);
void	exec_cmd_list(t_list *cmds, t_data *data);
// exec_utils.c
void	setup_redirs(t_command *cmd, int *old_stdin, int *old_stdout);
char	*error_ret_null(t_data *data, int error, char *s1, char *s2);
void	kill_children(void);
void	wait_children(t_data *data, int last_pid);
void	clear_cmd(void *cmd_void);
// exec_builtin.c
char	is_builtin(char *cmd_name);
void	exec_builtin(t_command *cmd, t_data *data, char **argv);
// exec_cmd.c
void	add_g_pids(pid_t pid);
int		exec_cmd(t_command *cmd, char **argv, t_data *data);
// find_cmd.c
char	*find_cmd(char *cmd, t_data *data, char *allocated);

//builtins/
void	echo_cmd(char **argv, t_data *data);
void	exit_cmd(char **argv, t_data *data);
void	pwd_cmd(t_data *data);
void	cd_cmd(char **argv, t_data *data);
void	env_cmd(t_data *data);
void	unset_cmd(char **argv, t_data *data);
void	export_cmd(char **argv, t_data *data);

#endif
