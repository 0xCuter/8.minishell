/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:30:48 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/23 15:11:41 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s_cpy;
	int		s_len;

	s_len = 0;
	while (s[s_len])
		++s_len;
	s_cpy = (char *) malloc((s_len + 1) * sizeof(char));
	if (s_cpy == NULL)
	{
		errno = ENOMEM;
		return (s_cpy);
	}
	while (s_len + 1)
	{
		s_cpy[s_len] = s[s_len];
		--s_len;
	}
	return (s_cpy);
}
