/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:01:49 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/26 16:47:30 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WAIT_PROMPT "> "
#define METACHARACTERS " \t\n\v\f\r|<>\"'"
#define METACHARACTERS_WHITE_SPACES " \t\n\v\f\r"
#define METACHARACTERS_NO_WHITE_SPACES "|<>\"'"

//Returns index of the first appearing char in `line` from `set`
//End of `line` if none
static char	*ft_str_chrset(const char *line, const char *set)
{
	int		i;
	char	*r;
	char	*last_r;

	if (*line == 0)
		return ((char *)line);
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
	if (ft_str_chrset(meta + 1, METACHARACTERS_NO_WHITE_SPACES) != line + ft_strlen(line))
		write(2, ft_str_chrset(meta + 1, METACHARACTERS_NO_WHITE_SPACES), 1);
	else
		write(2, "newline", 7);
	if ((meta[0] == '<' && meta[1] == '<') || (meta[0] == '>' && meta[1] == '>'))
		write(2, meta + 1, 1);
	write(2, "'\n", 2);
}

//Returns a malloc'd string of the metacharacter's argument
static char	*get_meta_arg(char *meta)
{
	char	*meta_sub;
	char	*meta_trimmed;
	char	*meta_arg;

	meta_sub = ft_substr(meta, 0,
		ft_str_chrset(meta + 1, METACHARACTERS_NO_WHITE_SPACES) - meta);
	meta_trimmed = ft_strtrim(meta_sub, METACHARACTERS);
	if (*meta_trimmed == 0)
	{
		free(meta_sub);
		free(meta_trimmed);
		return (NULL);
	}
	meta_arg = ft_substr(meta_trimmed, 0,
		ft_str_chrset(meta_trimmed + 1, METACHARACTERS_WHITE_SPACES) - meta_trimmed);
	free(meta_sub);
	free(meta_trimmed);
	return (meta_arg);
}

// static char	*replace_vars(char *s, t_data *data, int *size)
// {
// 	char	*r;
// 	char	*var;
// 	char	*var_name_end;
// 	char	*envar;
// 	char	*temp;
// 	char	*temp2;
// 	int		i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '$')
// 		{
// 			var_name_end = ft_str_chrset(s + i, METACHARACTERS_WHITE_SPACES);
// 			if (*var_name_end == 0)
// 				var = ft_substr(s + i + 1, 0, var_name_end - s + i - 2);
// 			else
// 				var = ft_substr(s + i + 1, 0, var_name_end - s + i - 1);
// 			envar = find_envar(data, var);
// 			if (envar)
// 			{
// 				size += ft_strlen(var);
// 				i += ft_strlen(var);
// 				temp2 = s;
// 				s = ft_substr(s, 0, i - 1);
// 				temp = s;
// 				s = ft_strjoin(s, ft_substr(envar, 0, ft_strchr(envar, '=') - envar));
// 				free(temp);
// 				temp = s;
// 				r = ft_strjoin(s, ft_substr(s, i, ft_strlen(s)));
// 				free(temp);
// 				free(temp2);
// 			}
// 			else
// 				++i;
// 		}
// 		else
// 			++i;
// 	}
// 	free(s);
// 	return (r);
// }

// static char	*replace(char *meta, char *s, t_data *data)
// {
// 	// char	*r;
// 	// char	*temp;
// 	// int		i;
// 	int		size;

// 	size = 0;
// 	if (*meta == '"')
// 		s = replace_vars(s, data, &size);
// 	// r = malloc((ft_strlen(s) + size + 1) * sizeof(char));
// 	// i = 0;
// 	// while (s[i])
// 	// {
// 	// 	temp = s;
// 	// 	s = ft_strjoin(s, "\n");
// 	// 	free(temp);
// 	// 	temp = s;
// 	// 	s = ft_strjoin(s, s);
// 	// 	free(temp);
// 	// 	++i;
// 	// }
// 	// free(s);
// 	return (s);
// 	// return (r);
// }

static char	*get_quotes_content(char *quote_1, char *quote_2)
{
	char	*r;
	int		i;

	r = malloc((quote_2 - quote_1) * sizeof(char));
	if (r == NULL)
		return (NULL);
	i = 0;
	while (quote_1 + i++ < quote_2 - 1)
		r[i - 1] = quote_1[i];
	r[i - 1] = 0;
	return (r);
}

static void	replace_quotes(char **meta, char **line, t_data *data)
{
	(void)data;
	char	*next_quote;
	char	*add_line;
	char	*new_line;

	next_quote = ft_strchr(*meta + 1, *meta[0]);
	if (next_quote == NULL)
		*meta = next_quote;
	else
	{
		add_line = get_quotes_content(*meta, next_quote);
		new_line = ft_str_replace(*line, *meta - *line, next_quote - *line + 1, add_line);
		*meta = *meta - *line + new_line + ft_strlen(add_line);
		free(*line);
		free(add_line);
		*line = new_line;
	}
}

//Checks if the line has a correct syntax
char	*check_syntax(char *line, t_data *data)
{
	char	*meta;
	char	*meta_arg;

	meta = ft_str_chrset(line, METACHARACTERS_NO_WHITE_SPACES);
	while (meta && meta != line + ft_strlen(line))
	{
		if ((meta[0] == '<' && meta[1] == '<') || (meta[0] == '>' && meta[1] == '>'))
			++meta;
		if (meta[0] == '\'' || meta[0] == '"')
			replace_quotes(&meta, &line, data);
		else
		{
			meta_arg = get_meta_arg(meta);
			if (meta_arg == NULL)
			{
				free(meta_arg);
				print_error(meta, line);
				return (line);
			}
			free(meta_arg);
			meta = ft_str_chrset(meta + 1, METACHARACTERS_NO_WHITE_SPACES);
		}
	}
	return (line);
}
