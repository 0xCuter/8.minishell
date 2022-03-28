/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:01:49 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/28 15:15:12 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*replace_here_doc(char *meta, char *meta_arg, char *line)
// {
// 	char	*l;
// 	char	*replace;
// 	char	*temp;
// 	char	*r;

// 	replace = NULL;
// 	while (1)
// 	{
// 		l = readline(WAIT_PROMPT);
// 		if (l == NULL || !ft_strcmp(l, meta_arg))
// 			break ;
// 		if (replace == NULL)
// 			replace = l;
// 		else
// 		{
// 			temp = replace;
// 			replace = ft_strjoin(replace, l);
// 			free(temp);
// 			free(l);
// 		}
// 	}
// 	r = ft_substr(line, 0, meta - line);
// 	temp = r;
// 	r = ft_strjoin(r, replace);
// 	free(temp);
// 	temp = r;
// 	l = ft_substr(line, meta - line, ft_strlen(line));
// 	r = ft_strjoin(r, l);
// 	free(temp);
// 	free(l);
// 	return (r);
// }

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
char	*get_meta_arg(char *meta)
{
	char	*meta_sub;
	char	*meta_trimmed;
	char	*meta_arg;

	meta_sub = ft_substr(meta, 0,
		ft_str_chrset(meta + 1, METACHARS_NO_WHITE_SPACES) - meta);
	meta_trimmed = ft_strtrim(meta_sub, METACHARS);
	if (*meta_trimmed == 0)
	{
		free(meta_sub);
		free(meta_trimmed);
		return (NULL);
	}
	meta_arg = ft_substr(meta_trimmed, 0,
		ft_str_chrset(meta_trimmed + 1, METACHARS_WHITE_SPACES) - meta_trimmed);
	free(meta_sub);
	free(meta_trimmed);
	return (meta_arg);
}

//Checks if the line has a correct syntax
//Returns the position of the error
char	*check_syntax(char *line, t_data *data)
{
	(void)data;
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
			// replace_quotes(&meta, &line, data);
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
			meta_arg = get_meta_arg(meta);
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
