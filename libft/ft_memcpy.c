/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:12:08 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/25 14:49:37 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	char	*dp;
	char	*sp;

	dp = (char *) s1;
	sp = (char *) s2;
	if (dp == 0 && sp == 0)
		return (s1);
	while (n)
	{
		*dp = *sp;
		--n;
		++dp;
		++sp;
	}
	return (s1);
}
