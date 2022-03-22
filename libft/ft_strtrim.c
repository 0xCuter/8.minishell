/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:06:35 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/25 15:19:49 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char s, char const *set)
{
	while (*set)
	{
		if (s == *set)
			return (1);
		++set;
	}
	return (0);
}

static int	get_mid_start(char const *s, char const *set)
{
	int	c;

	c = 0;
	while (in_set(s[c], set) && *s)
		++c;
	return (c);
}

static int	get_mid_end(char const *s, char const *set, int s1_len)
{
	int	c;

	c = s1_len - 1;
	if (c > 0)
	{
		while (in_set(s[c], set) && s[c])
			--c;
	}
	return (c);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	char	*rs;
	int		mid_start;
	int		mid_end;

	if (s1 == 0)
		return (NULL);
	mid_start = get_mid_start(s1, set);
	mid_end = get_mid_end(s1, set, ft_strlen(s1));
	if (mid_start >= mid_end + 1)
	{
		s = malloc(sizeof(char));
		*s = 0;
		return (s);
	}
	s = malloc((mid_end - mid_start + 2) * sizeof(char));
	if (s == NULL)
		return (NULL);
	rs = s;
	while (mid_start < mid_end + 1)
		*s++ = s1[mid_start++];
	*s = 0;
	return (rs);
}
