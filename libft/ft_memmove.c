/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:16:23 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/25 14:51:52 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	char	*dest;
	char	*src;

	dest = (char *) s1;
	src = (char *) s2;
	if (dest == 0 && src == 0)
		return (s1);
	if (s1 < s2)
	{
		while (n)
		{
			*dest++ = *src++;
			--n;
		}
	}
	else
	{
		while (n)
		{
			dest[n - 1] = src[n - 1];
			--n;
		}
	}
	return (s1);
}
