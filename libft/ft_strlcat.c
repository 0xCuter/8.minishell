/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:06:57 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/23 15:12:14 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dest_len;
	size_t	d_end;

	src_len = 0;
	while (src[src_len])
		++src_len;
	dest_len = 0;
	while (dest[dest_len])
		++dest_len;
	if (size == 0)
		return (src_len);
	if (size < dest_len)
		return (size + src_len);
	d_end = dest_len;
	i = 0;
	while (src[i] != 0 && d_end < size - 1)
		dest[d_end++] = src[i++];
	dest[d_end++] = 0;
	return (src_len + dest_len);
}
