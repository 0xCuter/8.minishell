/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:38:16 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/02 14:53:37 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Prints the error and exits with `errno` code
void	error(const char *error)
{
	perror(error);
	exit(errno);
}

//Removes a string part between `start` and `end` by replacing it with `fit`
//Returns a newly malloc'd string
char	*ft_str_replace(char *s, int start, int end, char *fit)
{
	char	*r;
	char	*part;
	char	*temp;

	if (s == NULL)
		return (NULL);
	part = ft_substr(s, 0, start);
	r = ft_strjoin(part, fit);
	free(part);
	part = ft_substr(s, end, ft_strlen(s));
	temp = r;
	r = ft_strjoin(r, part);
	free(temp);
	free(part);
	return (r);
}

//Returns 1 if `r` is quoted in `s` by double quotes
//Returns 2 if `r` is quoted in `s` by single quotes
//Else 0
char	in_quotes(const char *s, char *r)
{
	char	*quote;
	char	*quote_end;

	quote = ft_str_chrset(s, METACHARS_QUOTES);
	while (quote && *quote)
	{
		quote_end = ft_strchr(quote + 1, *quote);
		if (quote_end == NULL)
			return (0);
		if (quote < r && r < quote_end)
		{
			if (*quote == '"')
				return (1);
			return (2);
		}
		quote = ft_str_chrset(quote_end + 1, METACHARS_QUOTES);
	}
	return (0);
}

//Returns index of the first appearing char in `s` from `set` that is not quoted
//End of `s` if none
char	*ft_str_chrset_ign_quotes(const char *s, const char *set)
{
	int		i;
	char	*r;
	char	*last_r;

	if (*s == 0)
		return ((char *)s);
	last_r = (char *)s + ft_strlen(s);
	i = 0;
	while (i < (int)ft_strlen(set))
	{
		r = ft_strchr(s, set[i]);
		while (r && in_quotes(s, r))
			r = ft_strchr(r + 1, set[i]);
		if (r && r < last_r)
			last_r = r;
		++i;
	}
	return (last_r);
}

//Returns index of the first appearing char in `s` from `set`
//End of `s` if none
char	*ft_str_chrset(const char *s, const char *set)
{
	int		i;
	char	*r;
	char	*last_r;

	if (*s == 0)
		return ((char *)s);
	last_r = (char *)s + ft_strlen(s);
	i = 0;
	while (i < (int)ft_strlen(set))
	{
		r = ft_strchr(s, set[i]);
		if (r && r < last_r)
			last_r = r;
		++i;
	}
	return (last_r);
}

//Returns index of the first appearing char in `s` that is *not* from `set`
//End of `s` if none
char	*ft_str_chrset_rev(const char *s, const char *set)
{
	int		i;
	char	*r;
	char	*last_r;

	if (*s == 0)
		return ((char *)s + ft_strlen(s));
	last_r = (char *)s;
	i = 0;
	while (i < (int)ft_strlen(set))
	{
		r = ft_strchr(s, set[i]);
		if (r && r <= last_r)
			last_r = r + 1;
		++i;
	}
	return (last_r);
}

//Frees a pointer and sets it to `NULL`
void	free_null(void **elem)
{
	free(*elem);
	*elem = NULL;
}
