/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:12:07 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/09 17:28:27 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_meta_arg_with_quotes(char *meta, int *size, t_data *data)
{
	char	*arg;
	char	*end_quote;
	int		i;

	i = 0;
	end_quote = ft_strchr(meta + 1, *meta);
	if (end_quote == NULL)
		return (NULL);
	arg = ft_substr(meta, 0, end_quote - meta + 1);
	replace_quotes(&arg, data, &i);
	*size += i + 2;
	return (arg);
}

static char	*get_meta_arg_simple(char *meta, int *meta_sub_size)
{
	char	*arg;

	if (*meta == 0)
		return (NULL);
	else
		arg = ft_substr(meta, 0, ft_str_chrset(meta + 1, METACHARS) - meta);
	if (arg == NULL)
		return (NULL);
	*meta_sub_size += ft_strlen(arg);
	if (*arg == 0)
	{
		free(arg);
		return (NULL);
	}
	return (arg);
}

//Sets meta after the first whitespaces
//True if it reaches the end of the string
static char	move_to_first_char(char **meta, int *meta_sub_size)
{
	char	*first_char;

	first_char = ft_str_chrset_rev(*meta + 1, METACHARS_WHITE_SPACES);
	if (ft_strchr(METACHARS_NO_QUOTES, *first_char)
		&& ft_strchr(METACHARS_NO_QUOTES, *first_char)[0] != 0)
		return (1);
	if (first_char)
	{
		*meta_sub_size += first_char - *meta;
		*meta = first_char;
	}
	return (0);
}

//Returns a malloc'd string of the metacharacter's argument
//Sets `meta_sub_size` to the length of the metacharacter's argument
// (with the inital whitespaces)
//NULL if none
char	*get_meta_arg(char *meta, int *meta_sub_size, t_data *data)
{
	char	*arg;

	*meta_sub_size = 0;
	if (move_to_first_char(&meta, meta_sub_size))
		return (NULL);
	if (*meta == '\'' || *meta == '"')
	{
		arg = get_meta_arg_with_quotes(meta, meta_sub_size, data);
		if (arg == NULL)
			return (NULL);
	}
	else
	{
		arg = get_meta_arg_simple(meta, meta_sub_size);
		if (arg == NULL)
			return (NULL);
	}
	return (arg);
}
