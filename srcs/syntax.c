/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:01:49 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/25 18:40:32 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Returns index of the first appearing char in `line` from `set`
//NULL if none
static char	*ft_str_chrset(const char *line, const char *set)
{
	int		i;
	char	*r;
	char	*last_r;

	last_r = (char *)line + ft_strlen(line);
	i = 0;
	while (i < (int)ft_strlen(set))
	{
		r = ft_strchr(line, set[i]);
		if (r && r < last_r)
			last_r = r;
		++i;
	}
	return (last_r);
}

// static char	*replace_here_doc(char *meta, char *meta_final, char *line)
// {
// 	char	*l;
// 	char	*replace;
// 	char	*temp;
// 	char	*r;

// 	replace = NULL;
// 	while (1)
// 	{
// 		l = readline(WAIT_PROMPT);
// 		if (l == NULL || !ft_strcmp(l, meta_final))
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
	if (ft_str_chrset(meta + 1, METACHARACTERS_NO_WHITE_SPACES) != line + ft_strlen(line))
		write(2, ft_str_chrset(meta + 1, METACHARACTERS_NO_WHITE_SPACES), 1);
	else
		write(2, "newline", 7);
	if ((meta[0] == '<' && meta[1] == '<') || (meta[0] == '>' && meta[1] == '>'))
		write(2, meta + 1, 1);
	write(2, "'\n", 2);
}

void	check_syntax(char *line)
{
	char	*meta;
	char	*meta_sub;
	char	*meta_trimmed;
	char	*meta_final;

	meta = ft_str_chrset(line, METACHARACTERS_NO_WHITE_SPACES);
	while (meta != line + ft_strlen(line))
	{
		if ((meta[0] == '<' && meta[1] == '<') || (meta[0] == '>' && meta[1] == '>'))
			++meta;
		meta_sub = ft_substr(meta, 0, ft_str_chrset(meta + 1, METACHARACTERS_NO_WHITE_SPACES) - meta);
		meta_trimmed = ft_strtrim(meta_sub, METACHARACTERS);
		meta_final = ft_substr(meta_trimmed, 0, ft_str_chrset(meta_trimmed + 1, METACHARACTERS_WHITE_SPACES) - meta_trimmed);
		if (*meta_final == 0)
		{
			print_error(meta, line);
			return ;
		}
		meta = ft_str_chrset(meta + 1, METACHARACTERS_NO_WHITE_SPACES);
	}
	return ;
}
