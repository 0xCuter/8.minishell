/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:24:47 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/25 15:11:07 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_substr2(char const *s, char *rs, unsigned int start, size_t len)
{
	size_t	c;

	c = 0;
	while (c != len && s[start + c])
	{
		rs[c] = s[start + c];
		++c;
	}
	rs[c] = 0;
	return (rs);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*rs;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	if (start > ft_strlen(s))
	{
		rs = malloc(sizeof(char));
		*rs = 0;
		return (rs);
	}
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	rs = malloc((len + 1) * sizeof(char));
	if (rs == NULL)
		return (NULL);
	return (ft_substr2(s, rs, start, len));
}
