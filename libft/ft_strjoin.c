/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:49:21 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/29 09:26:41 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*copy_str(char *src, char *dest)
{
	while (*src)
	{
		*dest = *src;
		++src;
		++dest;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s1p;
	char	*s2p;
	char	*p;
	char	*rp;
	int		p_len;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	s1p = (char *) s1;
	s2p = (char *) s2;
	p_len = 1;
	while (*s1p++)
		++p_len;
	while (*s2p++)
		++p_len;
	p = malloc(p_len * sizeof(char));
	if (p == NULL)
		return (NULL);
	rp = p;
	p = copy_str((char *) s1, p);
	p = copy_str((char *) s2, p);
	*p = 0;
	return (rp);
}
