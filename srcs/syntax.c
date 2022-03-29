/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:01:49 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/29 11:12:14 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *meta, char *line)
{
	ft_putstr_fd("-minishell: syntax error near unexpected token `", 2);
	if (ft_str_chrset(meta + 1, METACHARS_NO_WHITE_SPACES) != line + ft_strlen(line))
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

	meta_sub = ft_substr(meta, 0,
		ft_str_chrset(meta + 1, METACHARS_NO_WHITE_SPACES) - meta);
	if (meta_sub_size)
		*meta_sub_size = ft_strlen(meta_sub);
	meta_trimmed = ft_strtrim(meta_sub, METACHARS);
	if (*meta_trimmed == 0)
	{
		free(meta_sub);
		return (NULL);
	}
	free(meta_sub);
	return (meta_trimmed);
}

//Checks if the line has a correct syntax
//Returns the position of the error
char	*check_syntax(char *line)
{
	char	*last_meta;
	char	*meta;
	char	*meta_arg;

	meta = ft_str_chrset(line, METACHARS_NO_WHITE_SPACES);
	while (meta && meta != line + ft_strlen(line))
	{
		if ((meta[0] == '<' && meta[1] == '<') || (meta[0] == '>' && meta[1] == '>'))
		{
			last_meta = meta;
			++meta;
		}
		if (meta[0] == '\'' || meta[0] == '"')
		{
			last_meta = meta;
			meta = ft_strchr(meta + 1, meta[0]);
			if (meta == NULL)
			{
				print_error(last_meta, line);
				return (last_meta);
			}
			++meta;
		}
		else
		{
			last_meta = meta;
			meta_arg = get_meta_arg(meta, NULL);
			if (meta_arg == NULL)
			{
				free(meta_arg);
				print_error(meta, line);
				return (last_meta);
			}
			free(meta_arg);
			meta = ft_str_chrset(meta + 1, METACHARS_NO_WHITE_SPACES);
		}
	}
	return (meta);
}
