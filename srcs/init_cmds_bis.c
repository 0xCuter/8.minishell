/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirs_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 08:50:48 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/10 08:52:34 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//|
char	init_pipe(t_command *cmd, char *stdout_pipe, char **cur_char)
{
	if (*stdout_pipe)
	{
		cmd->stdout_piped = 1;
		*stdout_pipe = 0;
		return (1);
	}
	else
	{
		cmd->stdin_piped = 1;
		*stdout_pipe = 1;
		++*cur_char;
	}
	return (0);
}

//Inits the argument list, or adds an argument
static void	add_arg(t_command *cmd, char *arg)
{
	if (cmd->argv == NULL)
	{
		cmd->argv = ft_calloc(2, sizeof(char *));
		if (cmd->argv == NULL)
			return ;
		cmd->argv[0] = arg;
	}
	else
	{
		cmd->argv = add_line(arg, cmd->argv);
		free(arg);
	}
}

//Adds the current token to the command argv list
//Also replaces the environment variables and quotes in that token
void	add_argv(t_command *cmd, char **cur_char, t_data *data)
{
	char	*arg;
	int		i;
	int		arg_len;

	arg_len = ft_str_chrset_ign_quotes(*cur_char,
			METACHARS_NO_QUOTES) - (*cur_char);
	arg = ft_substr(*cur_char, 0, arg_len);
	if (arg == NULL)
		return ;
	*cur_char += arg_len;
	i = 0;
	if (arg && arg[0] == 0)
	{
		free(arg);
		return ;
	}
	while (arg && arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
			replace_quotes(&arg, data, &i);
		else
			++i;
	}
	if (arg)
		add_arg(cmd, arg);
}
