/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:49:25 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/05 01:19:37 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//Modified strjoin for prompt that returns a copy of's2' if 's1' is NULL.
//Frees 's1' after 'ft_strjoin'.
char	*mod_strjoin(char *s1, char *s2)
{
	char	*str;

	if (!s1)
		return (ft_strdup(s2));
	str = ft_strjoin(s1, s2);
	if (!str)
		error("MALLOC");
	free(s1);
	return (str);
}
