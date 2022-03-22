/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:06:21 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/23 15:12:08 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*sp;

	sp = NULL;
	while (*s)
	{
		if (*s == (char) c)
		{
			sp = (char *) s;
			return (sp);
		}
		++s;
	}
	if (*s == (char) c)
	{
		sp = (char *) s;
		return (sp);
	}
	return (NULL);
}
