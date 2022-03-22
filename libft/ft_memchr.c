/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:21:41 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/25 14:55:20 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*sp;
	size_t			i;

	sp = (unsigned char *) s;
	i = 0;
	while (i != n)
	{
		if (sp[i] == (unsigned char) c)
			return (&sp[i]);
		++i;
	}
	return (NULL);
}
