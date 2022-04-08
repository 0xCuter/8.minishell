/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:35:08 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/08 13:28:16 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//If the var is "?", it is expanded to `exit_status`
//Else, the variable is replaced by a simple "$"
static char	*replace_var_special(char *s, t_data *data, int *i, char *var_end)
{
	char	*temp;
	char	*status_str;

	temp = s;
	if (*var_end == '?')
	{
		status_str = ft_itoa(data->exit_status);
		s = ft_str_replace(s, *i, var_end - s + 1, status_str);
		free(status_str);
	}
	else if (*var_end == '\'' || *var_end == '"')
		s = ft_str_replace(s, *i, var_end - s, "");
	else
		s = ft_str_replace(s, *i, var_end - s, "$");
	free(temp);
	++*i;
	return (s);
}

//Returns a new string with the variable replaced in `s`
//The "$" is at `s + *i` and the length of the var is added to `*i`
static char	*replace_var(char *s, t_data *data, int *i)
{
	char	*var;
	char	*var_name_end;
	char	*envar_value;
	char	*temp;

	var_name_end = ft_str_chrset(s + *i + 1, VAR_CHARS);
	if (var_name_end == s + *i + 1)
		s = replace_var_special(s, data, i, var_name_end);
	else
	{
		var = ft_substr(s + *i + 1, 0, var_name_end - (s + *i) - 1);
		envar_value = get_env(data, var);
		if (envar_value == NULL)
			envar_value = "";
		temp = s;
		s = ft_str_replace(s, *i, var_name_end - s, envar_value);
		*i += ft_strlen(envar_value);
		free(temp);
		free(var);
	}
	return (s);
}

//Returns a new string with all the `env` variables replaced
char	*replace_vars(char *s, t_data *data)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '$' && in_quotes(s, s + i) != 2)
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

//Replaces quotes in the string `s` with their literal value
//If the quotes are double, also replaces the environment variables inside
void	replace_quotes(char **s, t_data *data, int *pos)
{
	char	*next_quote;
	char	*add_line;
	char	*new_line;
	int		size_before;

	next_quote = ft_strchr(*s + *pos + 1, (*s)[*pos]);
	if (next_quote == NULL)
	{
		++*pos;
		return ;
	}
	size_before = next_quote - 1 - (*s + *pos);
	add_line = get_quotes_content(*s + *pos, next_quote, data);
	new_line = ft_str_replace(*s, *pos, next_quote - *s + 1, add_line);
	free(*s);
	*pos += size_before + (ft_strlen(add_line) - size_before);
	free(add_line);
	*s = new_line;
}
