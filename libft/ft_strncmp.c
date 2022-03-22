/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:12:56 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/25 14:57:22 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1p;
	unsigned char	*s2p;

	s1p = (unsigned char *) s1;
	s2p = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (*s1p == *s2p && *s1p != 0 && *s2p != 0 && --n)
	{
		++s1p;
		++s2p;
	}
	return (*s1p - *s2p);
}
