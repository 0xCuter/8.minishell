/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:01:49 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/08 18:12:09 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Writes the syntax error on STDERR
static void	print_syntax_error(char *meta, char *line)
{
	ft_putstr_fd("-minishell: syntax error near unexpected token `", 2);
	if (meta && *meta == '|')
		write(2, "||", 2);
	else if (meta && ft_str_chrset(meta + 1, METACHARS_NO_WHITE_SPACES) != line + ft_strlen(line))
		write(2, ft_str_chrset(meta + 1, METACHARS_NO_WHITE_SPACES), 1);
	else
		write(2, "newline", 7);
	write(2, "'\n", 2);
}

static char	*get_met_arg_with_quotes(char *meta, int *meta_sub_size, t_data *data)
{
	char	*meta_sub;
	char	*end_quote;
	int		i;

	i = 0;
	end_quote = ft_strchr(meta + 1, *meta);
	if (end_quote == NULL)
		return (NULL);
	meta_sub = ft_substr(meta, 0, end_quote - meta + 1);
	replace_quotes(&meta_sub, data, &i);
	*meta_sub_size += i + 2;
	return (meta_sub);
}

//Returns a malloc'd string of the metacharacter's argument
//Sets `meta_sub_size` to the length of the metacharacter's argument (with whitespaces)
//NULL if none
char	*get_meta_arg(char *meta, int *meta_sub_size, t_data *data)
{
	char	*meta_sub;
	char	*first_char;

	*meta_sub_size = 0;
	first_char = ft_str_chrset_rev(meta + 1, METACHARS_WHITE_SPACES);
	if (ft_strchr(METACHARS, *first_char))
		return (NULL);
	if (*first_char)
	{
		*meta_sub_size += first_char - meta;
		meta = first_char;
	}
	if (*meta == '\'' || *meta == '"')
	{
		meta_sub = get_met_arg_with_quotes(meta, meta_sub_size, data);
		if (meta_sub == NULL)
			return (NULL);
	}
	else
	{
		meta_sub = ft_substr(meta, 0, ft_str_chrset(meta + 1, METACHARS) - meta);
		if (meta_sub == NULL)
			return (NULL);
		*meta_sub_size += ft_strlen(meta_sub);
	}
	if (*meta_sub == 0)
	{
		free(meta_sub);
		return (NULL);
	}
	return (meta_sub);
}

//Returns 1 if the metacharacter has no argument and writes error
//Else 0
static char	meta_no_arg(char *line, char **meta, t_data *data)
{
	char	*meta_arg;
	int		meta_arg_size;

	meta_arg = get_meta_arg(*meta, &meta_arg_size, data);
	if (meta_arg == NULL || *meta_arg == '|')
	{
		if (*meta && **meta == '|')
		{
			if (ft_str_chrset(*meta + 1, METACHARS_NO_WHITE_SPACES) != line + ft_strlen(line))
				*meta = ft_str_chrset(*meta + 1, METACHARS_NO_WHITE_SPACES);
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

//Checks if the line has a correct syntax
//Returns 1 if it finds one, else 0
char	check_syntax(char *line, t_data *data)
{
	char	*last_meta;
	char	*meta;

	if (line == NULL)
	{
		data->exit_status = 258;
		return (1);
	}
	meta = ft_str_chrset(line, METACHARS_NO_WHITE_SPACES);
	while (meta && *meta && meta < line + ft_strlen(line))
	{
		if ((meta[0] == '<' && meta[1] == '<')
			|| (meta[0] == '>' && meta[1] == '>'))
		{
			last_meta = meta;
			++meta;
		}
		if (meta[0] == '\'' || meta[0] == '"')
		{
			last_meta = meta;
			meta = ft_strchr(meta + 1, meta[0]);
			if (meta == NULL)
				meta = last_meta + 1;
			else
				meta = ft_str_chrset(meta + 1, METACHARS_NO_WHITE_SPACES);
		}
		else
		{
			if (meta_no_arg(line, &meta, data))
			{
				data->exit_status = 258;
				return (1);
			}
			if (meta && *meta)
				meta = ft_str_chrset(meta + 1, METACHARS_NO_WHITE_SPACES);
		}
	}
	return (0);
}
