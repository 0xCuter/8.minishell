/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:24:48 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/23 15:11:15 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1p;
	unsigned char	*s2p;

	s1p = (unsigned char *) s1;
	s2p = (unsigned char *) s2;
	while (n)
	{
		if (*s1p != *s2p)
			return (*s1p - *s2p);
		++s1p;
		++s2p;
		--n;
	}
	return (0);
}
