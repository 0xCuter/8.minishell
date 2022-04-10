/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:01:49 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/10 15:25:20 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Writes the syntax error on STDERR
static void	print_syntax_error(char *meta, char *line)
{
	ft_putstr_fd("-minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	if (meta && *meta == '|')
		ft_putstr_fd("||", STDERR_FILENO);
	else if (meta && *meta != 0
		&& ft_str_chrset(meta + 1, METACHARS_NO_WHITE_SPACES)
		!= line + ft_strlen(line))
		write(2, ft_str_chrset(meta + 1, METACHARS_NO_WHITE_SPACES), 1);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

//Returns 1 if the metacharacter has no argument and writes error
//Else 0
static char	meta_no_arg(char *line, char **meta, t_data *data)
{
	char	*meta_arg;
	int		meta_arg_size;

	meta_arg = get_meta_arg(*meta, &meta_arg_size, data);
	if ((meta_arg == NULL
			&& ft_str_chrset(*meta + 1, METACHARS_NO_WHITE_SPACES)[0] == 0)
			|| (meta_arg != NULL && *meta_arg == '|'))
	{
		if (*meta && **meta == '|')
		{
			if (**meta != 0)
				++*meta;
			else
				*meta = NULL;
		}
		print_syntax_error(*meta, line);
		free(meta_arg);
		return (1);
	}
	free(meta_arg);
	*meta += meta_arg_size;
	return (0);
}

//Checks if the first pipe character has a token before it
static char	check_first_pipes(char *line, char **meta)
{
	*meta = ft_str_chrset_rev(line, METACHARS_WHITE_SPACES);
	if (*meta && **meta == '|')
	{
		if ((*meta)[1] == '|')
			ft_putendl_fd(
				"-minishell: syntax error near unexpected token `||'",
				STDERR_FILENO);
		else
			ft_putendl_fd(
				"-minishell: syntax error near unexpected token `|'",
				STDERR_FILENO);
		return (1);
	}
	return (0);
}

static void	skip_quotes(char **last_meta, char **meta)
{
	*last_meta = *meta;
	*meta = ft_strchr(*meta + 1, (*meta)[0]);
	if (*meta == NULL)
		*meta = *last_meta + 1;
	else
		*meta = ft_str_chrset(*meta + 1, METACHARS_NO_WHITE_SPACES);
}

//Checks if the line has a correct syntax
//Returns 1 if it finds one, else 0
char	check_syntax(char *line, t_data *data)
{
	char	*meta;
	char	*last_meta;

	if (check_first_pipes(line, &meta))
		return (err_ret_1(data, 258));
	meta = ft_str_chrset(meta, METACHARS_NO_WHITE_SPACES);
	while (meta && *meta)
	{
		if ((meta[0] == '<' && meta[1] == '<')
			|| (meta[0] == '>' && meta[1] == '>'))
		{
			last_meta = meta;
			++meta;
		}
		if (meta[0] == '\'' || meta[0] == '"')
			skip_quotes(&last_meta, &meta);
		else
		{
			if (meta_no_arg(line, &meta, data))
				return (err_ret_1(data, 258));
			if (meta && *meta)
				meta = ft_str_chrset(meta + 1, METACHARS_NO_WHITE_SPACES);
		}
	}
	return (0);
}
