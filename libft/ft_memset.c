/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:10:04 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/23 15:12:15 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void	*b, int c, size_t len)
{
	char	*p;

	p = (char *) b;
	while (len)
	{
		*p = c;
		++p;
		--len;
	}
	return (b);
}
