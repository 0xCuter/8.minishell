/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:06:23 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/23 15:11:56 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*sp;
	int		appeared;

	appeared = 0;
	sp = NULL;
	while (*s)
	{
		if (*s == (char) c)
		{
			sp = (char *) s;
			appeared = 1;
		}
		++s;
	}
	if (*s == (char) c)
	{
		sp = (char *) s;
		appeared = 1;
	}
	if (appeared)
		return (sp);
	else
		return (NULL);
}
