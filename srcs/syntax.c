/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:01:49 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/05 11:16:32 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Writes the syntax error on STDERR
static void	print_syntax_error(char *meta, char *line)
{
	ft_putstr_fd("-minishell: syntax error near unexpected token `", 2);
	if (ft_str_chrset(meta + 1, METACHARS_NO_WHITE_SPACES)
		!= line + ft_strlen(line))
		write(2, ft_str_chrset(meta + 1, METACHARS_NO_WHITE_SPACES), 1);
	else
		write(2, "newline", 7);
	write(2, "'\n", 2);
}

//Returns a malloc'd string of the metacharacter's argument
//Sets `meta_sub_size` to the length of the metacharacter's
// argument (with whitespaces)
//NULL if none
char	*get_meta_arg(char *meta, int *meta_sub_size)
{
	char	*meta_sub;
	char	*meta_trimmed;

	meta_sub = ft_substr(meta,
			0, ft_str_chrset(meta + 1, METACHARS_NO_WHITE_SPACES) - meta);
	if (meta_sub_size)
		*meta_sub_size = ft_strlen(meta_sub);
	meta_trimmed = ft_strtrim(meta_sub, METACHARS);
	free(meta_sub);
	if (*meta_trimmed == 0)
		return (NULL);
	return (meta_trimmed);
}

//Returns 1 if the metacharacter has no argument
//Else 0
static char	meta_no_arg(char *line, char **last_meta, char **meta)
{
	char	*meta_arg;

	*last_meta = *meta;
	meta_arg = get_meta_arg(*meta, NULL);
	if (meta_arg == NULL)
	{
		free(meta_arg);
		print_syntax_error(*meta, line);
		return (1);
	}
	free(meta_arg);
	*meta = ft_str_chrset(*meta + 1, METACHARS_NO_WHITE_SPACES);
	return (0);
}

//Checks if the line has a correct syntax
//Returns 1 if it finds one, else 0
char	check_syntax(char *line)
{
	char	*last_meta;
	char	*meta;

	meta = ft_str_chrset(line, METACHARS_NO_WHITE_SPACES);
	while (meta && meta != line + ft_strlen(line))
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
			if (meta_no_arg(line, &last_meta, &meta))
				return (1);
		}
	}
	return (0);
}
