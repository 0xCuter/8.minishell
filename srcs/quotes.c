/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:35:08 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/28 10:59:16 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Returns a new string with the variable replaced
static char	*replace_var(char *s, t_data *data, int *i)
{
	char	*var;
	char	*var_name_end;
	char	*envar;
	char	*envar_value;
	char	*temp;

	var_name_end = ft_str_chrset(s + *i, METACHARS_WHITE_SPACES);
	var = ft_substr(s + *i + 1, 0, var_name_end - (s + *i) - 1);
	envar = find_envar(data, var);
	if (envar)
	{
		free(var);
		envar_value = ft_substr(envar, ft_strchr(envar, '=') + 1 - envar, ft_strlen(envar));
		temp = s;
		s = ft_str_replace(s, *i, var_name_end - s, envar_value);
		free(temp);
		*i += ft_strlen(envar_value);
		free(envar_value);
	}
	else
	{
		temp = s;
		s = ft_str_replace(s, *i, var_name_end - s, "");
		free(temp);
		free(var);
	}
	return (s);
}

//Returns a new string with all the `env` variables replaced
static char	*replace_vars(char *s, t_data *data)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			s = replace_var(s, data, &i);
		else
			++i;
	}
	return (s);
}

//Returns a new string with the content between `quote_1` and `quote_2`
static char	*get_quotes_content(char *quote_1, char *quote_2, t_data *data)
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
	if (*quote_1 == '"')
		r = replace_vars(r, data);
	return (r);
}

//Replaces quotes in a line with their literal value
//Also replaces the variables inside if the quotes are double
void	replace_quotes(char **meta, char **line, t_data *data)
{
	char	*next_quote;
	char	*add_line;
	char	*new_line;

	next_quote = ft_strchr(*meta + 1, *meta[0]);
	// if (next_quote == NULL)
	// {
	// 	print_error(*meta, *line);
	// 	*meta = next_quote;
	// }
	// else
	{
		add_line = get_quotes_content(*meta, next_quote, data);
		new_line = ft_str_replace(*line, *meta - *line, next_quote - *line + 1, add_line);
		*meta = *meta - *line + new_line + ft_strlen(add_line);
		free(*line);
		free(add_line);
		*line = new_line;
	}
}
