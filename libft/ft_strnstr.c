/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:35:37 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/23 15:12:09 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	char	*s1p;
	char	*s2p;
	char	*rp;
	size_t	n_cpy;

	if (*s2 == 0)
		return ((char *) s1);
	if (n == 0)
		return (NULL);
	s1p = (char *) s1;
	s2p = (char *) s2;
	while (*s1p && n)
	{
		rp = s1p;
		n_cpy = n;
		while (n-- && *s1p == *s2p && *s1p++ && *s2p++)
			;
		if (*s2p == 0)
			return (rp);
		s1p = rp;
		++s1p;
		n = n_cpy - 1;
		s2p = (char *) s2;
	}
	return (NULL);
}
