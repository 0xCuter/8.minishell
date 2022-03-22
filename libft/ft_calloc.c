/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:30:50 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/25 12:01:22 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*array;
	char	*p;
	int		size_total;

	size_total = count * size;
	array = malloc(size_total);
	if (array == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	p = (char *) array;
	while (size_total)
	{
		*p = 0;
		++p;
		--size_total;
	}
	return (array);
}
